#include <cstdio>
#include <iostream>
#include <cstdint>
#include <vector>
#include <random>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <string>

#include <string.h>

#include "VLS_wrapper.h"

using std::cout;
using std::endl;

// Print utility.
void print(const Yamaha::VOCALOID::VLSModule::VLSError& error) {
    std::string head = (error.result == Yamaha::VOCALOID::VLSModule::kResultSuccess) ? "Success: " : "Error: ";
    cout << head << error.result << ": " << error.message << endl;
}

#define CONV_ERROR(err, verror) \
do {\
	verror.result = err.result;\
	strncpy(verror.message, err.message.c_str(), sizeof(verror.message));\
	verror.message[sizeof(verror.message) - 1] = 0;\
} while (0)

#define CHECK_ERROR(error) \
do {\
if (error.result != Yamaha::VOCALOID::VLSModule::kResultSuccess)\
    return error;\
} while (0)


VLS_Error VLS_process(
		int16_t **data,
		int &data_size, 
		const char *lyrics, 
		const VLS_Note *vnotes, 
		int notes_size,
		const int bpm,
		const int bankId) 
{
	using namespace Yamaha::VOCALOID::VLSModule;
	VLS_Error verror;
	VLSError error { kResultSuccess, "" };

	// pitchbend can be empty.
	std::vector<VLSPitchBend> pitchBends;
	// vibrato can be empty.
	std::vector<VLSVibrato> vibratos;

	int32_t voiceBankID = bankId;    // Tianyi.
	int32_t tempo = bpm;      // 120.00 BPM.

	std::vector<VLSNote> notes;
	for (int i = 0; i < notes_size; ++i)
	{
		notes.push_back({ vnotes[i].note, vnotes[i].start, vnotes[i].duration, "", "" });
	} 

	// set sequence data and get a sequence handle.
	VLSSequenceHandle handle = VLSSetSequenceData(voiceBankID, tempo, lyrics, notes, pitchBends, vibratos, &error);
	CONV_ERROR(error, verror);
    CHECK_ERROR(verror);

	std::vector<int16_t> buffer; 

	// use handle returned VLSSetSequenceData().
	VLSRenderAudio(handle, &buffer, nullptr, &error);
	CONV_ERROR(error, verror);
    CHECK_ERROR(verror);

	data_size = buffer.size();
	*data = new int16_t[data_size];
	if (*data == nullptr)
	{
		cout << "out of memory" << endl;
		return verror;
	}
	memcpy(*data, buffer.data(), sizeof(int16_t) * data_size);

    return verror;
}

void VLS_start(const char *path)
{
	Yamaha::VOCALOID::VLSModule::VLSError error { Yamaha::VOCALOID::VLSModule::kResultSuccess, "" };
	// First VLSInit() need to be called.
	Yamaha::VOCALOID::VLSModule::VLSInit(path, &error);
	if (error.result != Yamaha::VOCALOID::VLSModule::kResultSuccess)
	{
		cout << "VLSInit failed: " << error.message << endl;
        exit(-1);
	}
}

void VLS_stop()
{
	Yamaha::VOCALOID::VLSModule::VLSError error { Yamaha::VOCALOID::VLSModule::kResultSuccess, "" };
    Yamaha::VOCALOID::VLSModule::VLSExit(&error);
	print(error);
}