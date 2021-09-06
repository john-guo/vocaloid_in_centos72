#include "VLS_api.h"

typedef struct VLS_Note {
    int note;
    int start;
    int duration;
} VLS_Note;

#define MAX_VLS_ERROR_LEN 1024

typedef struct VLS_Error {
    int result;
    char message[1024];
} VLS_Error;

extern "C"
{
VLS_Error VLS_process(int16_t **data, int &data_size, const char *lyrics, const VLS_Note *notes, int notes_size, const int bpm = 12000, const int bankId = 0);
void VLS_start(const char *path);
void VLS_stop();
}
