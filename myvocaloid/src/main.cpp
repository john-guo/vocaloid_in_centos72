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

using std::cout;
using std::endl;

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

	saveMonoWaveFile((out + ".wav").c_str(), 44100, buffer);
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
