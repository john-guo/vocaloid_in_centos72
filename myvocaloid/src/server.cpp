//
//  VOCALOID Light Synthesis API Sample.
//  main.cpp
//  Version 3.0.0d
//
//  Copyright (c) 2017- Yamaha Corporation. All rights reserved.
//

#include <cstdio>
#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <limits.h>
#include <unistd.h>

#include "VLS_api.h"

extern "C"
{
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswresample/swresample.h>
}

using std::cout;
using std::endl;


#define INBUF_SIZE 4096
 
void audio_encode_example(const char *filename,const short *in_buffer,unsigned int in_buf_byte_size)
{
    AVCodec *codec;
    AVCodecContext *c= NULL;
    AVFrame *frame;
    AVPacket pkt;
    int i, ret;
    int buffer_size;
    FILE *f;
    uint16_t *samples;
 
    printf("Audio encoding\n");
 
    codec = avcodec_find_encoder(AV_CODEC_ID_MP3);
    if (!codec) {
        fprintf(stderr, "codec not found\n");
        exit(1);
    }
 
    c= avcodec_alloc_context3(codec);
 
    c->bit_rate = 64000;
    c->sample_rate = 44100;
    c->channels = 1;
    c->sample_fmt = AV_SAMPLE_FMT_S16;
    c->channel_layout = AV_CH_LAYOUT_MONO;
    
    if (avcodec_open2(c, codec, NULL) < 0) {
        fprintf(stderr, "could not open codec\n");
        exit(1);
    }
 
    f = fopen(filename, "wb");
     if (!f) {
         fprintf(stderr, "could not open %s\n", filename);
         exit(1);
     }
  
    /* frame containing input raw audio */
    frame = av_frame_alloc();
    if (!frame) {
        fprintf(stderr, "could not allocate audio frame\n");
        exit(1);
    }

    frame->nb_samples     = c->frame_size;
    frame->format         = c->sample_fmt;
    frame->channel_layout = c->channel_layout;

    /* the codec gives us the frame size, in samples,
    * we calculate the size of the samples buffer in bytes */
    buffer_size = av_samples_get_buffer_size(NULL, c->channels, c->frame_size,
                                            c->sample_fmt, 0);
    samples = (uint16_t*)av_malloc(buffer_size);
    if (!samples) {
        fprintf(stderr, "could not allocate %d bytes for samples buffer\n",
                buffer_size);
        exit(1);
    }
    /* setup the data pointers in the AVFrame */
    ret = avcodec_fill_audio_frame(frame, c->channels, c->sample_fmt,
                                (const uint8_t*)samples, buffer_size, 0);
    if (ret < 0) {
        fprintf(stderr, "could not setup audio frame\n");
        exit(1);
    }

    int rsize = in_buf_byte_size % buffer_size;
    int frames = in_buf_byte_size / buffer_size;
    for(i=0;i<frames+1;i++) {
        if (i == frames && rsize == 0)
            break;

        av_init_packet(&pkt);
        pkt.data = NULL; // packet data will be allocated by the encoder
        pkt.size = 0;

        void *cframe = (char *)in_buffer+i*buffer_size;
        if (i == frames && rsize > 0)
        {
            bzero(samples, buffer_size);
            memcpy(samples, cframe, rsize);
        }
        else
        {
            memcpy(samples, cframe, buffer_size);
        }

        ret = avcodec_send_frame(c, frame);
        if (ret < 0) {
            fprintf(stderr, "error avcodec_send_frame\n");
            exit(1);
        }
        ret = avcodec_receive_packet(c, &pkt);
        if (ret < 0) {
            if (ret ==  AVERROR(EAGAIN))
            {
                fprintf(stderr, "warnning avcodec_receive_packet EAGAIN\n");
                continue;
            }
            char errbuf[1000] = {0};
            av_strerror(ret, errbuf, 1000);
            fprintf(stderr, "error avcodec_receive_packet %d %s\n", ret, errbuf);
            exit(1);
        }

        fwrite(pkt.data, 1, pkt.size, f);
        av_packet_unref(&pkt);
    }

    fclose(f);
  
    cout << "free sample" << endl;
    av_freep(&samples);
    cout << "free frame" << endl;
    av_frame_free(&frame);
    cout << "close codec" << endl;
    avcodec_close(c);
    cout << "free codec" << endl;
    av_free(c);
}


// WAVE file operation. 
struct riff_header {
    uint32_t fileSize;
    uint8_t fileType[4];

    void setType(char a, char b, char c, char d) {
        fileType[0] = a;
        fileType[1] = b;
        fileType[2] = c;
        fileType[3] = d;
    }

    void write(FILE* outfile) {
        uint8_t RIFF[] = { 'R', 'I', 'F', 'F' };
        fwrite(RIFF, 1, sizeof(RIFF), outfile);
        fwrite(&fileSize, 1, sizeof(fileSize), outfile);
        fwrite(fileType, 1, sizeof(fileType), outfile);
    }
};

struct riff_chunk {
    uint32_t chunkSize;
    uint8_t chunkID[4];

    void setType(char a, char b, char c, char d) {
        chunkID[0] = a;
        chunkID[1] = b;
        chunkID[2] = c;
        chunkID[3] = d;
    }

    uint32_t size() {
        return 8 + chunkSize;
    }

    void write(FILE* outfile) {
        fwrite(chunkID, 1, sizeof(chunkID), outfile);
        fwrite(&chunkSize, 1, sizeof(chunkSize), outfile);
    }
};

struct riff_wave_fmt {
    uint16_t AudioFormat;
    uint16_t NumChannels;
    uint32_t SampleRate;
    uint32_t ByteRate;
    uint16_t BlockAlign;
    uint16_t BitsPerSample;

    riff_wave_fmt() {
        AudioFormat = 1;
        NumChannels = 1;
        SampleRate = 44100;
        BitsPerSample = 16;
        ByteRate = SampleRate * NumChannels * BitsPerSample / 8;
        BlockAlign = (uint16_t)(NumChannels * BitsPerSample / 8);
    }

    uint32_t size() {
        return 16;
    }

    void write(FILE* outfile) {
        fwrite(&AudioFormat, 1, sizeof(AudioFormat), outfile);
        fwrite(&NumChannels, 1, sizeof(NumChannels), outfile);
        fwrite(&SampleRate, 1, sizeof(SampleRate), outfile);
        fwrite(&ByteRate, 1, sizeof(ByteRate), outfile);
        fwrite(&BlockAlign, 1, sizeof(BlockAlign), outfile);
        fwrite(&BitsPerSample, 1, sizeof(BitsPerSample), outfile);
    }
};

struct riff_wave_data {
    riff_wave_fmt* m_pFmt;
    const std::vector<int16_t>* m_pData;

    riff_wave_data(riff_wave_fmt* pFmt, const std::vector<short>* pData) {
        m_pFmt = pFmt;
        m_pData = pData;
    }

    uint32_t size() {
        return (uint32_t)(m_pData->size() * m_pFmt->NumChannels * m_pFmt->BitsPerSample / 8);
    }

    void write(FILE* outfile) {
        for (size_t i = 0; i < m_pData->size(); ++i) {
            fwrite(&((*m_pData)[i]), 1, sizeof(short), outfile);
        }
    }
};

bool saveMonoWaveFile(const char* filepath, uint32_t sampleRate, const std::vector<int16_t>& audioData) {
    FILE* outputFile;
    outputFile = fopen(filepath, "wb");
    if (outputFile == NULL) {
        return false;
    }
    if (audioData.empty()) {
        return false;
    }

    riff_header header;
    riff_chunk fmt_chunk;
    riff_chunk data_chunk;
    riff_wave_fmt wave_fmt;
    riff_wave_data wave_data(&wave_fmt, &audioData);

    header.setType('W', 'A', 'V', 'E');
    fmt_chunk.setType('f', 'm', 't', ' ');
    data_chunk.setType('d', 'a', 't', 'a');

    fmt_chunk.chunkSize = wave_fmt.size();
    data_chunk.chunkSize = wave_data.size();
    header.fileSize = fmt_chunk.size() + data_chunk.size();

    wave_fmt.SampleRate = sampleRate;

    header.write(outputFile);
    fmt_chunk.write(outputFile);
    wave_fmt.write(outputFile);
    data_chunk.write(outputFile);
    wave_data.write(outputFile);

    fclose(outputFile);

    cout << "save: " << filepath << endl;

    return true;
}

// Print utility.
void print(const Yamaha::VOCALOID::VLSModule::VLSError& error) {
    std::string head = (error.result == Yamaha::VOCALOID::VLSModule::kResultSuccess) ? "Success: " : "Error: ";
    cout << head << error.result << ": " << error.message << endl;
}

std::string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

std::string getDirectory(const std::string& str)
{
  size_t found;
  found=str.find_last_of("/\\");
  return str.substr(0,found);
}

std::string getFilename(const std::string &str) {
	size_t found;
	found = str.find_last_of("/\\");
	return str.substr(found+1);
}


void process(const std::string &path, const std::string &text, int textSize, const std::string &music, const std::string &out) {
	cout << "___" << __FUNCTION__ << "___" << endl;

	using namespace Yamaha::VOCALOID::VLSModule;
	VLSError error;

	// First VLSInit() need to be called.
	VLSInit(path, &error);
	print(error);

	// set notes.
	std::vector<VLSNote> notes;

	int noteCount = music.length();
	const int size = textSize;
	//const int noteNumber[] = { 60, 62, 64, 65, 67, 69, 71, 72 };
	//const int noteNumber[] = { 69, 67, 64, 62, 60, 62, 60, 57, 55, 54 };
	//int noteCount = sizeof(noteNumber) / sizeof(noteNumber[0]);
	int time = 0;
	int noteLength = 480;
	for (int i = 0; i < size; ++i) {
		// No need to set note's lyric and phonetic.
		VLSNote note{
			music[i % noteCount], time, noteLength, "", ""
		};
		notes.push_back(note);

		time += noteLength;
	}

	// pitchbend can be empty.
	std::vector<VLSPitchBend> pitchBends;
	// vibrato can be empty.
	std::vector<VLSVibrato> vibratos;

	int32_t voiceBankID = 0;    // Tianyi.
	int32_t tempo = 12000;      // 120.00 BPM.

	std::string lyrics = text;

	// set sequence data and get a sequence handle.
	VLSSequenceHandle handle = VLSSetSequenceData(voiceBankID, tempo, lyrics, notes, pitchBends, vibratos, &error);
	print(error);

	std::vector<int16_t> buffer;

	// use handle returned VLSSetSequenceData().
	VLSRenderAudio(handle, &buffer, nullptr, &error);
	print(error);

	VLSExit(&error);
	print(error);

    audio_encode_example((out + ".mp3").c_str(), buffer.data(), buffer.size() * sizeof(int16_t));
}



int main(int argc, char* argv[])
{
	std::string exepath = getexepath();

	if (argc < 5) {
		cout << getFilename(exepath) << " text size sequence out" << endl;
		return 0;
	}

    std::string path = getDirectory(exepath);
    std::string text(argv[1]);
    int size =  atoi(argv[2]);
    std::string sequence(argv[3]);
    std::string out(argv[4]);
	
	process(path, text, size, sequence, out);
    return 0;
}
