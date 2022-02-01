using Grpc.Core;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using MyVocaloid;
using System.Diagnostics;
using NAudio;
using NAudio.Wave;
using NAudio.MediaFoundation;
using System.IO;
using System.Threading;
using Google.Protobuf;
using Microsoft.International.Converters.PinYinConverter;

namespace WinVocaloid
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            MediaFoundationApi.Startup();
        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            MediaFoundationApi.Shutdown();
        }

        class WaveStream16 : WaveProvider16
        {
            private short[] _buffer;
            private int _offset;
            public WaveStream16(short[] raw)
                :base(44100, 1)
            {
                _buffer = raw;
            }

            public override int Read(short[] buffer, int offset, int sampleCount)
            {
                if (_offset + sampleCount >= _buffer.Length)
                {
                    sampleCount = _buffer.Length - _offset;
                }
                if (sampleCount <= 0)
                    return 0;

                Buffer.BlockCopy(_buffer, _offset, buffer, offset, sampleCount);
                Debug.WriteLine($"Read Offset {offset} Count {sampleCount}");
                _offset += sampleCount;
                return sampleCount;
            }
        }

        //class WaveStream16NetStream : WaveProvider16
        //{
        //    private IAsyncStreamReader<SingReply> _reader;

        //    public WaveStream16NetStream(IAsyncStreamReader<SingReply> reader)
        //        : base(44100, 1)
        //    {
        //        _reader = reader;
        //    }

        //    public override int Read(short[] buffer, int offset, int sampleCount)
        //    {
        //        if (!_reader.MoveNext().Result)
        //            return 0;

        //        var reply = _reader.Current;
        //        if (reply.ReplyDataCase != SingReply.ReplyDataOneofCase.Chunk)
        //            throw new Exception("expect chunk");

        //        var buf = reply.Chunk.Data.Select(i => (short)i).ToArray();
        //        if (buf.Length > sampleCount)
        //            throw new Exception("chunk too large");

        //        sampleCount = buf.Length;
        //        Buffer.BlockCopy(buf, 0, buffer, offset, sampleCount);
        //        Debug.WriteLine($"Read Offset {offset} Count {sampleCount}");
        //        return sampleCount;
        //    }
        //}

        private string GetWslIpAddress(string distro = null)
        {
            var startInfo = new ProcessStartInfo("wsl.exe")
            {
                Arguments = $"{(string.IsNullOrWhiteSpace(distro) ? "" : $"-s {distro} ")}hostname -I",
                RedirectStandardOutput = true,
                CreateNoWindow = true,
                UseShellExecute = false,
            };

            var process = Process.Start(startInfo);
            process.WaitForExit();
            var ip = process.StandardOutput.ReadToEnd().TrimEnd();
            process.Dispose();
            return ip;
        }

        private int GetNote(char ch)
        {
            return ch;
        }

        private int GetBeatTime(int beat, int bpm)
        {
            float one = 6000.0f / bpm;
            return (int)Math.Round(LyricsBox.Beats[beat].factor * one * 1000);
        }

        private SingRequest GetRequest(int bpm)
        {
            StringBuilder sb = new StringBuilder();
            List<Note> notes = new List<Note>();
            int start = 0;
            foreach (var ch in lyricsBox1.Chars)
            {
                if (string.IsNullOrWhiteSpace(ch.Pinyin))
                    continue;

                sb.Append($"{ch.Pinyin} ");

                int time = GetBeatTime(ch.Beat, bpm);
                notes.Add(new Note { Note_ = GetNote(ch.Note), Start = start, Duration = time });
                start += time;
            }
            var lyrics = sb.ToString().TrimEnd();

            var request = new SingRequest { Bank = 0, Bpm = bpm, Lyrics = lyrics };
            request.Notes.AddRange(notes);

            return request;
        }


        private async void button1_Click(object sender, EventArgs e)
        {
            int bpm = Convert.ToInt32(textBox1.Text) * 100;
            if (bpm < 2000 || bpm > 30000)
            {
                MessageBox.Show("Wrong BPM[20.00,300.00]");
                return;
            }

            var ip = GetWslIpAddress();
            var channel = new Channel($"{ip}:50051", ChannelCredentials.Insecure);
            var client = new Vocaloid.VocaloidClient(channel);
            var request = GetRequest(bpm);
            using (var call = client.Sing(request))
            {
                var response = call.ResponseStream;
                if (await response.MoveNext())
                {
                    var reply = response.Current;
                    if (reply.ReplyDataCase != SingReply.ReplyDataOneofCase.Header)
                    {
                        throw new Exception("expect header");
                    }
                    Debug.WriteLine(reply.Header.Result);
                    Debug.WriteLine(reply.Header.Message);
                    if (reply.Header.Result == 0)
                    {
                        using (var ms = new MemoryStream())
                        {
                            while (await response.MoveNext())
                            {
                                reply = response.Current;
                                if (reply.ReplyDataCase != SingReply.ReplyDataOneofCase.Chunk)
                                    throw new Exception("expect chunk");

                                reply.Chunk.Data.WriteTo(ms);
                            }

                            ms.Seek(0, SeekOrigin.Begin);
                            using (var stream = new RawSourceWaveStream(ms, new WaveFormat(44100, 16, 1)))
                            using (var wout = new WaveOutEvent())
                            {
                                wout.Init(stream);
                                wout.Play();

                                while (wout.PlaybackState == PlaybackState.Playing)
                                {
                                    await Task.Delay(1000);
                                }

                                stream.Position = 0;
                                MediaFoundationEncoder.EncodeToMp3(stream, "song.mp3");
                            }
                        }

                        //var stream = new WaveStream16NetStream(response);
                        //WaveFileWriter.CreateWaveFile16("test.wav", stream.ToSampleProvider());
                        //MediaFoundationEncoder.EncodeToMp3(stream, "test.mp3", 64000);
                    }
                }
            }

            await channel.ShutdownAsync();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            var dialog = new SaveFileDialog()
            {
                Filter = "JSON|*.json",
                AddExtension = true,
            };
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                lyricsBox1.SaveFile(dialog.FileName);
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var dialog = new OpenFileDialog()
            {
                Filter = "JSON|*.json",
                AddExtension = true,
            };
            if (dialog.ShowDialog() == DialogResult.OK)
            {
                lyricsBox1.LoadFile(dialog.FileName);
            }
        }
    }
}
