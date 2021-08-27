//
//  VOCALOID Light Synthesis API.
//  VLS_api.h
//  Version 3.0.0d 
//
//  Copyright (c) 2017- Yamaha Corporation. All rights reserved.
//

#ifndef __VLS_API__
#define __VLS_API__

#define __VISIBILITY__ __attribute__((visibility("default")))

#include <cstdint>
#include <string>
#include <vector>

namespace Yamaha {
    namespace VOCALOID {
        namespace VLSModule __VISIBILITY__ {

            /**
            * @brief   Handle for a sequence.
            */
            typedef int32_t VLSSequenceHandle;
            
            /**
            * @brief   Handle for a part.
            */
            typedef int32_t VLSPartHandle;

            static const VLSSequenceHandle kInvalidSequenceHandle = -1;     //!< Invalid sequence handle value.
            static const VLSPartHandle kInvalidPartHandle = -1;             //!< Invalid part handle value.

            static const int32_t kMinTempo = 2000;          //!< Minimum tempo value (20.00 BPM).
            static const int32_t kMaxTempo = 30000;         //!< Maximum tempo value (300.00 BPM).
            static const int32_t kMinPitchBend = -8192;     //!< Minimum pitchbend value.
            static const int32_t kMaxPitchBend = 8191;      //!< Maximum pitchbend value.
            static const int32_t kMinVibrato = 0;           //!< Minimum vibrato value.
            static const int32_t kMaxVibrato = 127;         //!< Maximum vibrato value.

            /**
            * @brief   VOCALOID module's state.
            */
            typedef enum {
                kStateStopped,  //!< Not initialized or exited.
                kStateRunning,  //!< Initialized.
            } VLSState;

            /**
            * @brief   Language info.
            */
            typedef enum {
                kLanguageChinese = 4,    //!< Chinese.
            } VLSLanguage;

         
            /**
            * @brief   API result.
            */
            typedef enum {
                kResultSuccess,                 //!< Success.
                kResultArgumentError,           //!< One of the arguments is not valid.
                kResultNotInitialized,          //!< VOCALOID module is not initialized.
                kResultAlreadyInitialized,      //!< VOCALOID module is already initialized.
                kResultSetupFileLoadError,      //!< Failed to load a setup file.
                kResultVoiceBankLoadError,      //!< Failed to load VOCALOID databases.
                kResultDictionaryLoadError,     //!< Failed to (un)load a dictionary data.
                kResultInvalidSequenceHandle,   //!< A sequence handle is not valid.
                kResultInvalidLanguage,         //!< A language info is not valid.
                kResultInvalidVoiceBankID,      //!< A voice bank ID info is not valid.
                kResultInterruptedRender,       //!< Rendering process is interrupted.
                kResultInvalidTime,             //!< Time info is not valid.
                kResultInvalidTempo,            //!< Tempo info is not valid.
                kResultEmptyNoteList,           //!< A note list is empty.
                kResultInternalError,           //!< If an internal state of VOCALOID module is wrong, this error is set.
                kResultSequenceLoadError,       //!< Failed to load VSQX file.
                kResultInvalidTrack,            //!< A track is not valid.
                kResultInvalidPartHandle,       //!< A part handle is not valid.
                kResultEmptyEvent,              //!< There is no events.
            } VLSResult;

            /**
            * @brief    Error info.
            */
            struct VLSError {
                VLSResult result;
                std::string message;
            };

            /**
            * @brief    Tempo data.
            */
            struct VLSTempo {
                int32_t time;            //!< Tick Position.
                int32_t bpm;             //!< BPM [2000, 30000] = [20.00BPM, 300.00BPM]
            };

            /**
            * @brief    Part head.
            */
            struct VLSPartHead {
                VLSPartHandle partHandle;   //!< Part handle.
                int32_t time;               //!< Tick position.
                int32_t length;             //!< Part length (tick).
                std::string name;           //!< Part name.
            };

            /**
            * @brief    Note data.
            * @note     480 PPQN (Quarter note: 480 ticks).
            *           lyric:
                            Chinese: Pinyin.
                        phonetic: ASCII value.
            */
            struct VLSNote {
                int32_t noteNumber;     //!< Note number. [0, 127]
                int32_t time;           //!< Tick position.
                int32_t length;         //!< Note length (tick).
                std::string lyric;      //!< Lyric assigned to note.
                std::string phonetic;   //!< Phonetic symbol assigned to note.
            };

            /**
            * @brief    PitchBend data.
            * @note     PitchBend sensitivity is fixed 2.
                        0: No pitch change.
                        8191: Increase 2 semitones.
                        -8192: Decrease 2 semitones.
            */
            struct VLSPitchBend {
                int32_t time;   //!< Tick position.
                int32_t value;  //!< PitchBend value. [-8192, 8191]
            };

            /**
            * @brief    Vibrato data. [0, 127]
            * @note     0: No vibrato.
                        127: Deeper vibrato.
            */
            struct VLSVibrato {
                int32_t time;   //!< Tick position.
                int32_t value;  //!< Vibrato value. [0, 127]
            };

            /*
            * @brief    Returns VOCALOID module's state.
            * @return   kStateStopped: Not initialized or exited.
                        kStateRunning: initialized.
            */
            VLSState VLSGetState();

            /*
            * @brief        Starts and initializes VOCALOID Module.
            * @param[in]    resourcePath   VResources (VOCALOID data directory) path. 
            * @param[out]   error          (Optional) Error info.
                                kResultSuccess              : Success.
                                kResultAlreadyInitialized   : VOCALOID module is already initialized. 
                                kResultSetupFileLoadError   : Failed to load a setup file. Please check a resource files and path of argument.
                                kResultVoiceBankLoadError   : Failed to load VOCALOID databases. Please check a resource files and path of argument.
                                kResultDictionaryLoadError  : Failed to load a dictionary data. Please check a resource files and path of argument.
                                kResultInternalError        : If an internal state of VOCALOID module is wrong, this error is set. 
            * @note         This API needs to be called at first (except for VLSGetState()).
            */
            void VLSInit(
                const std::string& resourcePath, 
                VLSError* error = nullptr
            );

            /*
            * @brief        Finalizes and stops VOCALOID Module.
            * @param[out]   error   (Optional) Error info.
                                kResultSuccess              : Success.
                                kResultDictionaryLoadError  : Failed to unload a dictionary data. Please check a resource files.
                                kResultInterruptedRender    : If rendering processes are running, this error is set.
                                kResultInternalError        : If an internal state of VOCALOID module is wrong, this error is set. 
            */
            void VLSExit(VLSError* error = nullptr);

            /*
            * @brief        Returns count of notes corresponding to lyrics.
            * @param[in]    language    Language of lyrics.
            * @param[in]    lyrics      Lyrics.
            * @param[out]   error       (Optional) Error info.
                                kResultSuccess              : Success.
                                kResultNotInitialized       : VOCALOID module is not initialized. VLSInit() need to be called.
                                kResultInvalidLanguage      : A language info is not valid.
                                kResultInternalError        : If an internal state of VOCALOID module is wrong, this error is set.
            * @return       Count of notes corresponding to lyrics.
            * @note         lyrics:
                                Chinese: Pinyin.
            */
            int VLSGetNoteCountWithLyrics(
                VLSLanguage language, 
                const std::string& lyrics, 
                VLSError* error = nullptr
            );

            /*
            * @brief        Sets (Creates) sequence data to VOCALOID module and return sequence handle.
            * @param[in]    voiceBankID    Voice Bank ID.
            * @param[in]    tempo          Tempo Info. [2000, 30000] = [20.00 BPM, 300.00 BPM]
            * @param[in]    lyrics         Lyrics.
            * @param[in]    notes          Note list (Not allowed to be empty).
            * @param[in]    pitchBends     PitchBend list (Allowed to be empty).
            * @param[in]    vibratos       Vibrato list (Allowed to be empty).
            * @param[out]   error         (Optional) Error info.
                                kResultSuccess              : Success.
                                kResultNotInitialized       : VOCALOID module is not initialized. VLSInit() need to be called.
                                kResultInvalidLanguage      : A language info is not valid.
                                kResultInvalidVoiceBankID   : A voice bank ID is not valid.
                                kResultInvalidTime          : Time info is not valid.
                                kResultInvalidTempo         : Tempo info is not valid.
                                kResultEmptyNoteList        : A note list is empty.
                                kResultInternalError        : If an internal state of VOCALOID module is wrong, this error is set.
            * @return       Sequence handle.
            * @note         
                            Return value (Sequence handle) is needed to call VLSRenderAudio().
                            VoiceBankIDs are defined the developer's guide.
                            lyrics:
                                Chinese: Pinyin.
                            Each pitchbend value is clamped to [-8192, 8191].
                            Each vibrato value is clamped to [0, 127].
                            No need to set every note's lyric and phonetic.
            */
            VLSSequenceHandle VLSSetSequenceData(
                int32_t voiceBankID,
                int32_t tempo,
                const std::string& lyrics,
                const std::vector<VLSNote>& notes,
                const std::vector<VLSPitchBend>& pitchBends,
                const std::vector<VLSVibrato>& vibratos, 
                VLSError* error = nullptr
            );

            /*
            * @brief            1. Sets VOCALOID synthesized data to buffer.
                                2. (Optional) Sets lyric and phonetic symbol to each note.
            * @param[in]        sequenceHandle  Handle returned VLSSetSequenceData().
            * @param[out]       renderBuffer    Buffer for audio data.
            * @param[in, out]   notes           (Optional) Note list.
            * @param[out]       error           (Optional) Error info.
                                    kResultSuccess                  : Success.
                                    kResultArgumentError            : renderBuffer is not allocated.
                                    kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
                                    kResultInvalidSequenceHandle    : A sequence handle is not valid.
                                    kResultInterruptedRender        : Rendering process is interrupted.
                                    kResultInternalError            : If an internal state of VOCALOID module is wrong, this error is set.
            * @note             This API must be used only when the sequence is created by VLSSetSequenceData().
                                (If the sequence is loaded by VLSLoadSequence(), VLSRenderPartAudio() should be used.)
                                Audio data format: 16bit/44100Hz (mono).
                                Audio has additional 500ms data at the beginning of data.
                                    The data is added for a consonant of the first note.
                                "renderBuffer" vector container is allocated in the caller.
                                "notes" argument data should be the same as when called VLSSetSequenceData().
                                (All notes needs to be pushed before calling this API.)
                                If no need to set lyric and phonetic symbol to notes, "notes" argument can be omitted.
                                After this API, sequence data corresponding "sequenceHandle" is cleared.
            */
            void VLSRenderAudio(
                VLSSequenceHandle sequenceHandle,
                std::vector<int16_t>* renderBuffer,
                std::vector<VLSNote>* notes = nullptr,
                VLSError* error = nullptr
            );

            /*
            * @brief        Loads VSQX file on server.
            * @param[in]    sequencePath    Sequence file path (absolute path on server).
            * @param[out]   error           (Optional) Error info.
                                kResultSuccess                  : Success.
                                kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
                                kResultSequenceLoadError,       : Failed to load a VSQX file. Please check a VSQX files and path of argument.
                                kResultInvalidSequenceHandle    : A sequence handle generated in API is not valid.
                                kResultInternalError            : If an internal state of VOCALOID module is wrong, this error is set.
            * @return       Sequence handle.
            */
            VLSSequenceHandle VLSLoadSequence(
                const std::string& sequencePath,
                VLSError* error = nullptr
            );

            /*
            * @brief        Clears sequence data.
            * @param[in]    sequenceHandle  Sequence handle.
            * @param[out]   error           (Optional) Error info.
                                kResultSuccess                  : Success.
                                kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
            * @note         If the sequence is loaded by VLSLoadSequence(), this API should be used for unallocating memory.
            */
            void VLSClearSequence(
                VLSSequenceHandle sequenceHandle,
                VLSError* error = nullptr
            );

            /*
            * @brief        Returns whether the track exists.
            * @param[in]    sequenceHandle  Sequence handle.
            * @param[in]    track           Track number.
            * @param[out]   error           (Optional) Error info.
                                kResultSuccess                  : Success.
                                kResultArgumentError            : tempo is not allocated.
                                kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
                                kResultInvalidSequenceHandle    : A sequence handle is not valid.
            * @return       true:   The track exists.
                            false:  The track doesn't exist.
            */
            bool VLSHasTrack(
                VLSSequenceHandle sequenceHandle,
                int16_t track,
                VLSError* error = nullptr
            );

            /*
            * @brief        Gets tempos.
            * @param[in]    sequenceHandle  Sequence handle.
            * @param[out]   tempos          Tempo list.
            * @param[out]   error           (Optional) Error info.
                                kResultSuccess                  : Success.
                                kResultArgumentError            : tempo is not allocated.
                                kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
            */
            void VLSGetTempos(
                VLSSequenceHandle sequenceHandle,
                std::vector<VLSTempo>* tempos,
                VLSError* error = nullptr
            );

            /*
            * @brief        Gets part heads in the track.
            * @param[in]    sequenceHandle  Sequence handle.
            * @param[in]    track           Track number.
            * @param[out]   partHeads       Part head list.
            * @param[out]   error           (Optional) Error info.
                                kResultSuccess                  : Success.
                                kResultArgumentError            : tempo is not allocated.
                                kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
                                kResultInvalidSequenceHandle    : A sequence handle is not valid.
                                kResultInvalidTrack             : A track doesn't exist.
            */
            void VLSGetPartHeadsInTrack(
                VLSSequenceHandle sequenceHandle,
                int16_t track,
                std::vector<VLSPartHead>* partHeads,
                VLSError* error = nullptr
            );

            /*
            * @brief        Gets notes, pitchbend and vibrato in the part.
            * @param[in]    sequenceHandle  Sequence handle.
            * @param[in]    partHandle      Part handle.
            * @param[out]   notes           Note list.
            * @param[out]   pitchBends      (Optional) PitchBend list.
            * @param[out]   vibratos        (Optional) Vibrato list.
            * @param[out]   error           (Optional) Error info.
                                kResultSuccess                  : Success.
                                kResultArgumentError            : tempo is not allocated.
                                kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
                                kResultInvalidSequenceHandle    : A sequence handle is not valid.
                                kResultInvalidPartHandle        : A part handle is not valid.
                                kResultInternalError            : If an internal state of VOCALOID module is wrong, this error is set.
            */
            void VLSGetEventsInPart(
                VLSSequenceHandle sequenceHandle,
                VLSPartHandle partHandle,
                std::vector<VLSNote>* notes, 
                std::vector<VLSPitchBend>* pitchBends = nullptr,
                std::vector<VLSVibrato>* vibratos = nullptr,
                VLSError* error = nullptr
            );

            /*
            * @brief        Updates tempo data.
            * @param[in]    sequenceHandle  Sequence handle.
            * @param[in]    tempos          Tempo List (Not allowed to be empty).
            * @param[out]   error           (Optional) Error info.
                                kResultSuccess                  : Success.
                                kResultArgumentError            : tempo factor is not valid.
                                kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
                                kResultInvalidSequenceHandle    : A sequence handle is not valid.
                                kResultEmptyEvent               : A tempo list is empty.
                                kResultInvalidTime              : Time info is not valid.
                                kResultInvalidTempo             : Tempo info is not valid.
                                kResultInternalError            : If an internal state of VOCALOID module is wrong, this error is set.
            */
            void VLSUpdateTempo(
                VLSSequenceHandle sequenceHandle,
                const std::vector<VLSTempo>& tempos,
                VLSError* error = nullptr
            );

            /*
            * @brief        Updates the part data.
            * @param[in]    sequenceHandle  Sequence handle.
            * @param[in]    partHandle      Part handle.
            * @param[in]    voiceBankID     Voice Bank ID.
            * @param[in]    lyrics          Lyrics (Allowed to be empty).
            * @param[in]    notes           Note list (Allowed to be empty).
            * @param[in]    pitchBends      PitchBend list (Allowed to be empty).
            * @param[in]    vibratos        Vibrato list (Allowed to be empty).
            * @param[out]   error           (Optional) Error info.
                                kResultSuccess                  : Success.
                                kResultArgumentError            : tempo factor is not valid.
                                kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
                                kResultInvalidSequenceHandle    : A sequence handle is not valid.
                                kResultInvalidVoiceBankID       : A voice bank ID is not valid.
                                kResultInvalidTime              : Time info is not valid.
                                kResultInternalError            : If an internal state of VOCALOID module is wrong, this error is set.
            * @note         VoiceBankIDs are defined the developer's guide.
                            lyrics:
                                Chinese: Pinyin.
                            Each pitchbend value is clamped to [-8192, 8191].
                            Each vibrato value is clamped to [0, 127].
                            When argument "lyrics" is empty, each lyrics of notes is used.
                            When argument "lyrics" is not empty, all lyrics (and phonetics) of notes are updated.
                            When argument "notes" is empty, only lyrics (and phonetics) of notes are updated.
                            When argument "pitchBends" is empty, no pitchBends are updated.
                            When argument "vibratos" is empty, no vibratos are updated.
            */
            void VLSUpdatePart(
                VLSSequenceHandle sequenceHandle,
                VLSPartHandle partHandle,
                int32_t voiceBankID,
                const std::string& lyrics,
                const std::vector<VLSNote>& notes,
                const std::vector<VLSPitchBend>& pitchBends,
                const std::vector<VLSVibrato>& vibratos,
                VLSError* error = nullptr
            );

            /*
            * @brief            Sets VOCALOID synthesized data of the part to buffer.
            * @param[in]        sequenceHandle  Sequence handle.
            * @param[in]        partHead        Target part head.
            * @param[in]        voiceBankID     Voice Bank ID.
            * @param[out]       renderBuffer    Buffer for audio data.
            * @param[out]       error           (Optional) Error info.
                                    kResultSuccess                  : Success.
                                    kResultArgumentError            : renderBuffer is not allocated.
                                    kResultNotInitialized           : VOCALOID module is not initialized. VLSInit() need to be called.
                                    kResultInvalidSequenceHandle    : A sequence handle is not valid.
                                    kResultInterruptedRender        : Rendering process is interrupted.
                                    kResultInternalError            : If an internal state of VOCALOID module is wrong, this error is set.
            * @note             When the sequence is loaded by VLSLoadSequence(), this API should be used.
                                Audio data format: 16bit/44100Hz (mono).
                                Audio has additional 500ms data at the beginning of data.
                                   The data is added for a consonant of the first note.
                                "renderBuffer" vector container is allocated in the caller.
                                After this API, sequence data corresponding "sequenceHandle" is not cleared.
            */
            void VLSRenderPartAudio(
                VLSSequenceHandle sequenceHandle,
                const VLSPartHead& partHead,
                int32_t voiceBankID,
                std::vector<int16_t>* renderBuffer,
                VLSError* error = nullptr
            );
        }
    }
}
    
#endif /* defined(__VLS_API__) */
