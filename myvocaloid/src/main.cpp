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

// Coding sample.

/*
* rendering coding sample.
*/
#if 0
void sample1_simpleRendering(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    // set notes.
    std::vector<VLSNote> notes;

    const int size = 8;
    const int noteNumber[size] = { 60, 62, 64, 65, 67, 69, 71, 72 };

    int time = 0;
    int noteLength = 480;
    for (int i = 0; i < size; ++i) {
        // No need to set note's lyric and phonetic.
        VLSNote note{
            noteNumber[i], time, noteLength, "", ""
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

    std::string lyrics = "yi er san si wu liu qi ba";

    // set sequence data and get a sequence handle.
    VLSSequenceHandle handle = VLSSetSequenceData(voiceBankID, tempo, lyrics, notes, pitchBends, vibratos, &error);
    print(error);

    std::vector<int16_t> buffer;

    // use handle returned VLSSetSequenceData().
    VLSRenderAudio(handle, &buffer, nullptr, &error);
    print(error);

    VLSExit(&error);
    print(error);

    saveMonoWaveFile("sample1.wav", 44100, buffer);
}

/*
* checking state coding sample.
*/
void sample2_checkState(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    VLSState state = VLSGetState();
    // state must be 0 (kStateStopped).
    cout << "State [Before VLSInit()]: " << state << endl;

    VLSInit(path, &error);
    print(error);

    state = VLSGetState();
    // state must be 1 (kStateRunning).
    cout << "State [After VLSInit()]: " << state << endl;

    VLSExit(&error);
    print(error);

    state = VLSGetState();
    // state must be 0 (kStateStopped).
    cout << "State [After VLSExit()]: " << state << endl;
}

/*
* usage of getNoteCountWithLyrics() coding sample.
*/
void sample3_getNoteCountWithLyrics(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);

    std::string lyrics = "";

    lyrics = "ni hao";
    int32_t count = VLSGetNoteCountWithLyrics(kLanguageChinese, lyrics, &error);
    print(error);
    // count must be 2.
    cout << "count: " << count << endl;

    lyrics = "ming tian jian";
    count = VLSGetNoteCountWithLyrics(kLanguageChinese, lyrics, &error);
    print(error);
    // count must be 3.
    cout << "count: " << count << endl;

    VLSExit(&error);
    print(error);
}

/*
* set pitchbend coding sample.
*/
void sample4_setPitchBend(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    // set notes.
    std::vector<VLSNote> notes;

    const int size = 3;
    const int noteNumber[size] = { 60, 64, 65 };

    int time = 0;
    int noteLength = 960;
    for (int i = 0; i < size; ++i) {
        // No need to set note's lyric and phonetic.
        VLSNote note{
            noteNumber[i], time, noteLength, "", ""
        };
        notes.push_back(note);

        time += noteLength;
    }

    // set pitchbends.
    std::vector<VLSPitchBend> pitchBends;
    for (int t = 2400, pb = 0; t < noteLength * size; t += 10, pb += 1200) {
        VLSPitchBend pitchbend{
            t, pb
        };
        pitchBends.push_back(pitchbend);

        time += noteLength;
    }

    // vibrato can be empty.
    std::vector<VLSVibrato> vibratos;

    int32_t voiceBankID = 0;    // Tianyi.
    int32_t tempo = 8000;       // 80.00 BPM.

    std::string lyrics = "ni hao ma";

    // set sequence data and get a sequence handle.
    VLSSequenceHandle handle = VLSSetSequenceData(voiceBankID, tempo, lyrics, notes, pitchBends, vibratos, &error);
    print(error);

    std::vector<int16_t> buffer;

    // use handle returned VLSSetSequenceData().
    VLSRenderAudio(handle, &buffer, nullptr, &error);
    print(error);

    VLSExit(&error);
    print(error);

    saveMonoWaveFile("sample4.wav", 44100, buffer);
}

/*
* set vibrato coding sample.
*/
void sample5_setVibrato(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    // set notes.
    std::vector<VLSNote> notes;

    const int size = 3;
    const int noteNumber[size] = { 60, 64, 67 };

    int time = 0;
    int noteLength = 960;
    for (int i = 0; i < size; ++i) {
        // No need to set note's lyric and phonetic.
        VLSNote note{
            noteNumber[i], time, noteLength, "", ""
        };
        notes.push_back(note);

        time += noteLength;
    }

    // pitchbend can be empty.
    std::vector<VLSPitchBend> pitchBends;

    // vibrato can be empty.
    std::vector<VLSVibrato> vibratos;
    VLSVibrato vibrato1{
        0, 50
    };
    vibratos.push_back(vibrato1);
    // reset vibrato.
    VLSVibrato vibrato2{
        960, 0
    };
    vibratos.push_back(vibrato2);
    VLSVibrato vibrato3{
        1920, 127
    };
    vibratos.push_back(vibrato3);

    int32_t voiceBankID = 0;    // Tianyi.
    int32_t tempo = 8000;       // 80.00 BPM.

    std::string lyrics = "ni hao ma";

    // set sequence data and get a sequence handle.
    VLSSequenceHandle handle = VLSSetSequenceData(voiceBankID, tempo, lyrics, notes, pitchBends, vibratos, &error);
    print(error);

    std::vector<int16_t> buffer;

    // use handle returned VLSSetSequenceData().
    VLSRenderAudio(handle, &buffer, nullptr, &error);
    print(error);

    VLSExit(&error);
    print(error);

    saveMonoWaveFile("sample5.wav", 44100, buffer);
}

/*
* rendering and get note's lyric and phonetic coding sample.
*/
void sample6_getLyricAndPhonetic(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    // set notes.
    std::vector<VLSNote> notes;

    const int size = 8;
    const int noteNumber[size] = { 60, 62, 64, 65, 67, 69, 71, 72 };

    int time = 0;
    int noteLength = 480;
    for (int i = 0; i < size; ++i) {
        // No need to set note's lyric and phonetic.
        VLSNote note{
            noteNumber[i], time, noteLength, "", ""
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

    std::string lyrics = "yi er san si wu liu qi ba";

    // set sequence data and get a sequence handle.
    VLSSequenceHandle handle = VLSSetSequenceData(voiceBankID, tempo, lyrics, notes, pitchBends, vibratos, &error);
    print(error);

    std::vector<int16_t> buffer;

    // use handle returned VLSSetSequenceData().
    // set notes.
    VLSRenderAudio(handle, &buffer, &notes, &error);
    print(error);

    for (const auto& note : notes) {
        cout << note.lyric << "    " << note.phonetic << endl;
    }

    VLSExit(&error);
    print(error);

    saveMonoWaveFile("sample6.wav", 44100, buffer);
}

/*
* multiple calling render coding sample.
*/
void sample7_worker(int id) {
    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    const int arraySize = 8;
    const int noteNumber[arraySize] = { 60, 62, 64, 65, 67, 69, 71, 72 };

    const int size = 30;

    // set notes.
    std::vector<VLSNote> notes;

    std::random_device rnd;
    std::mt19937 mt(rnd());
    std::uniform_int_distribution<> randNumber(0, arraySize - 1);
    int time = 0;
    int noteLength = 960;

    for (int i = 0; i < size; ++i) {
        // No need to set note's lyric and phonetic.
        VLSNote note{
            noteNumber[randNumber(mt)], time, noteLength, "", ""
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

    std::string lyrics = "yi er san si wu liu qi ba jiu shi hei bai hui hong lan huang lu cheng zi he yi er san si wu liu qi ba jiu shi";

    // Measurement.
    auto start = std::chrono::system_clock::now();

    // set sequence data and get a sequence handle.
    VLSSequenceHandle handle = VLSSetSequenceData(voiceBankID, tempo, lyrics, notes, pitchBends, vibratos, &error);
    print(error);

    std::vector<int16_t> buffer;

    // use handle returned VLSSetSequenceData().
    VLSRenderAudio(handle, &buffer, nullptr, &error);
    print(error);

    // Measurement.
    auto end = std::chrono::system_clock::now();
    int64_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    cout << "Elapsed time [sample7_worker: before VLSSetSequenceData() - after VLSRenderAudio()]    " << elapsed << " [ms]" << endl;

    if (error.result == kResultSuccess) {
        std::ostringstream oss;
        oss << "sample7_" << id << ".wav" << std::flush;
        saveMonoWaveFile(oss.str().c_str(), 44100, buffer);
    }
}
void sample7_multipleCallingRender(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;

    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    try {
        int length = 4;
        std::vector<std::thread*> th;
        for (int i = 0; i < length; ++i) {
            std::thread *t = new std::thread(sample7_worker, i);
            th.push_back(t);
        }

        for (int i = 0; i < length; ++i) {
            th[i]->join();
        }

        for (auto& t : th) {
            delete t;
        }
    } catch (std::exception &ex) {
        std::cerr << ex.what() << endl;
    }

    VLSExit(&error);
    print(error);
}

/*
* loads VSQX file and gets sequence data.
*/
void sample8_LoadSequence(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    std::string sequencePath = "/home/user1/VOCALOID/vsqx/sample.vsqx"; // 1 track, 1 part.

    // Loads VSQX files.
    VLSSequenceHandle handle = VLSLoadSequence(sequencePath, &error);
    print(error);

    // Gets tempo.
    std::vector<VLSTempo> tempos;
    VLSGetTempos(handle, &tempos, &error);
    print(error);

    cout << "Tempo info." << endl;
    for (const auto& tempo : tempos) {
        cout << tempo.time << "    " << tempo.bpm << endl;
    }

    // Checks track. (Track starts at 1.)
    int16_t track = 1;
    bool hasTrack = VLSHasTrack(handle, track, &error);
    print(error);

    if (!hasTrack) {
        return;
    }

    // Gets partheads (part info).
    std::vector<VLSPartHead> partHeads;
    VLSGetPartHeadsInTrack(handle, track, &partHeads, &error);
    print(error);

    // Gets events in the part. (PitchBend and vibrato are optional.)
    std::vector<VLSNote> notes;
    std::vector<VLSPitchBend> pitchBends;
    std::vector<VLSVibrato> vibratos;
    VLSGetEventsInPart(handle, partHeads.at(0).partHandle, &notes, &pitchBends, &vibratos, &error);
    print(error);

    cout << "Notes info." << endl;
    for (const auto& note : notes) {
        cout << note.noteNumber << "    " << note.time << " " << note.length << "   " << note.lyric << "    " << note.phonetic << endl;
    }

    cout << "Pitch Bends info." << endl;
    for (const auto& pitchBend : pitchBends) {
        cout << pitchBend.time << "    " << pitchBend.value << endl;
    }

    cout << "Vibratos info." << endl;
    for (const auto& vibrato : vibratos) {
        cout << vibrato.time << "    " << vibrato.value << endl;
    }

    // Renderings the part. There is no update in this sample.
    int32_t voiceBankID = 0;    // Tianyi.
    std::vector<int16_t> buffer;
    VLSRenderPartAudio(handle, partHeads.at(0), voiceBankID, &buffer, &error);
    print(error);

    // Closes sequence.
    VLSClearSequence(handle, &error);
    print(error);

    VLSExit(&error);
    print(error);

    saveMonoWaveFile("sample8.wav", 44100, buffer);
}

/*
* updates tempo.
*/
void sample9_UpdateTempo(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    std::string sequencePath = "/home/user1/VOCALOID/vsqx/sample.vsqx";

    VLSSequenceHandle handle = VLSLoadSequence(sequencePath, &error);
    print(error);

    // Updates tempo.
    std::vector<VLSTempo> tempos;
    tempos.push_back(VLSTempo{ 0,16000 });

    VLSUpdateTempo(handle, tempos, &error);

    int16_t track = 1;
    std::vector<VLSPartHead> partHeads;
    VLSGetPartHeadsInTrack(handle, track, &partHeads, &error);
    print(error);

    int32_t voiceBankID = 0;    // Tianyi.
    std::vector<int16_t> buffer;
    VLSRenderPartAudio(handle, partHeads.at(0), voiceBankID, &buffer, &error);
    print(error);

    // Closes sequence.
    VLSClearSequence(handle, &error);
    print(error);

    VLSExit(&error);
    print(error);

    saveMonoWaveFile("sample9.wav", 44100, buffer);
}

/*
* updates note.
*/
void sample10_UpdateNotes(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    std::string sequencePath = "/home/user1/VOCALOID/vsqx/sample.vsqx";

    VLSSequenceHandle handle = VLSLoadSequence(sequencePath, &error);
    print(error);

    int16_t track = 1;
    std::vector<VLSPartHead> partHeads;
    VLSGetPartHeadsInTrack(handle, track, &partHeads, &error);
    print(error);

    std::vector<VLSNote> notes;
    VLSGetEventsInPart(handle, partHeads.at(0).partHandle, &notes, nullptr, nullptr, &error);
    print(error);

    // Updates lyrics of the first two notes.
    notes.at(0).lyric = "ni";
    notes.at(1).lyric = "hao";

    int32_t voiceBankID = 0;    // Tianyi.
    std::vector<VLSPitchBend> pitchBends;
    std::vector<VLSVibrato> vibratos;

    // updates part.
    // If some notes are updated individually, you must set argument "lyrics" to empty. 
    VLSUpdatePart(handle, partHeads.at(0).partHandle, voiceBankID, "", notes, pitchBends, vibratos, &error);


    std::vector<int16_t> buffer;
    VLSRenderPartAudio(handle, partHeads.at(0), voiceBankID, &buffer, &error);

    // Closes sequence.
    VLSClearSequence(handle, &error);
    print(error);

    VLSExit(&error);
    print(error);

    saveMonoWaveFile("sample10.wav", 44100, buffer);
}

/*
* updates whole lyrics.
*/
void sample11_UpdateWholeLyrics(const std::string& path) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    std::string sequencePath = "/home/user1/VOCALOID/vsqx/sample.vsqx";

    VLSSequenceHandle handle = VLSLoadSequence(sequencePath, &error);
    print(error);

    int16_t track = 1;
    std::vector<VLSPartHead> partHeads;
    VLSGetPartHeadsInTrack(handle, track, &partHeads, &error);
    print(error);

    std::vector<VLSNote> notes;
    VLSGetEventsInPart(handle, partHeads.at(0).partHandle, &notes, nullptr, nullptr, &error);
    print(error);

    int32_t voiceBankID = 0;    // Tianyi.
    std::vector<VLSPitchBend> pitchBends;
    std::vector<VLSVibrato> vibratos;

    // whole lyrics.
    std::string lyrics = 
        "yi er san si wu liu qi ba jiu shi \
        hei bai hui hong lan huang lu cheng zi he \
        yi er san si wu liu qi ba jiu shi \
        jiu ba qi liu wu si san er yi \
        yi er san si wu liu qi ba jiu shi \
        jiu ba qi liu wu si san er yi \
        yi er san si wu liu qi ba jiu shi \
        hei bai hui hong lan huang lu cheng zi he";

    // updates part.
    // If lyrics is not empty, each VLSNote.lyrics is ignored.
    VLSUpdatePart(handle, partHeads.at(0).partHandle, voiceBankID, lyrics, notes, pitchBends, vibratos, &error);


    std::vector<int16_t> buffer;
    VLSRenderPartAudio(handle, partHeads.at(0), voiceBankID, &buffer, &error);

    // Closes sequence.
    VLSClearSequence(handle, &error);
    print(error);

    VLSExit(&error);
    print(error);

    saveMonoWaveFile("sample11.wav", 44100, buffer);
}

#endif

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


/*
* loads VSQX file and gets sequence data.
*/
void process2(const std::string &path, const std::string &text, int textSize, const std::string &sequencePath, const std::string &out) {
    cout << "___" << __FUNCTION__ << "___" << endl;

    using namespace Yamaha::VOCALOID::VLSModule;
    VLSError error;

    // First VLSInit() need to be called.
    VLSInit(path, &error);
    print(error);

    //std::string sequencePath = "/home/user1/VOCALOID/vsqx/sample.vsqx"; // 1 track, 1 part.

    // Loads VSQX files.
    VLSSequenceHandle handle = VLSLoadSequence(sequencePath, &error);
    print(error);

    // Gets tempo.
    std::vector<VLSTempo> tempos;
    VLSGetTempos(handle, &tempos, &error);
    print(error);

    cout << "Tempo info." << endl;
    for (const auto& tempo : tempos) {
        cout << tempo.time << "    " << tempo.bpm << endl;
    }

    // Checks track. (Track starts at 1.)
    int16_t track = 1;
    bool hasTrack = VLSHasTrack(handle, track, &error);
    print(error);

    if (!hasTrack) {
        return;
    }

    // Gets partheads (part info).
    std::vector<VLSPartHead> partHeads;
    VLSGetPartHeadsInTrack(handle, track, &partHeads, &error);
    print(error);

    // Gets events in the part. (PitchBend and vibrato are optional.)
    std::vector<VLSNote> notes;
    std::vector<VLSPitchBend> pitchBends;
    std::vector<VLSVibrato> vibratos;
    VLSGetEventsInPart(handle, partHeads.at(0).partHandle, &notes, &pitchBends, &vibratos, &error);
    print(error);

    cout << "Notes info." << endl;
    for (const auto& note : notes) {
        cout << note.noteNumber << "    " << note.time << " " << note.length << "   " << note.lyric << "    " << note.phonetic << endl;
    }

    cout << "Pitch Bends info." << endl;
    for (const auto& pitchBend : pitchBends) {
        cout << pitchBend.time << "    " << pitchBend.value << endl;
    }

    cout << "Vibratos info." << endl;
    for (const auto& vibrato : vibratos) {
        cout << vibrato.time << "    " << vibrato.value << endl;
    }

    // Renderings the part. There is no update in this sample.
    int32_t voiceBankID = 0;    // Tianyi.
    std::vector<int16_t> buffer;
    VLSRenderPartAudio(handle, partHeads.at(0), voiceBankID, &buffer, &error);
    print(error);

    // Closes sequence.
    VLSClearSequence(handle, &error);
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
    //std::string path = "/home/user1/VOCALOID";
    std::string path = getDirectory(exepath);
    std::string text(argv[1]);
    int size =  atoi(argv[2]);
    std::string sequence(argv[3]);
    std::string out(argv[4]);
	
	process(path, text, size, sequence, out);
	/*
    std::string path = "/home/user1/VOCALOID";

    sample1_simpleRendering(path);
    sample2_checkState(path);
    sample3_getNoteCountWithLyrics(path);
    sample4_setPitchBend(path);
    sample5_setVibrato(path);
    sample6_getLyricAndPhonetic(path);
    sample7_multipleCallingRender(path);
  
    sample8_LoadSequence(path);
    sample9_UpdateTempo(path);
    sample10_UpdateNotes(path);
    sample11_UpdateWholeLyrics(path);
	*/
    return 0;
}
