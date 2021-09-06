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
                _offset += sampleCount;
                return sampleCount;
            }
        }

        private async void button1_Click(object sender, EventArgs e)
        {
            var channel = new Channel("172.30.55.100:50051", ChannelCredentials.Insecure);
            var client = new Vocaloid.VocaloidClient(channel);
            var request = new SingRequest { Bank = 0, Bpm = 12000, Lyrics = "ni" };
            request.Notes.Add(new Note { Note_ = 64, Start = 0, Duration = 440 });
            var result = await client.SingAsync(request);
            Debug.WriteLine(result.Result);
            Debug.WriteLine(result.Message);
            if (result.Result == 0)
            {
                var data = result.Data.Select(i => (short)i).ToArray();
                var stream = new WaveStream16(data);
                MediaFoundationEncoder.EncodeToMp3(stream, "test.mp3");
            }

            await channel.ShutdownAsync();
        }
    }
}
