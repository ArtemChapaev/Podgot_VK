#ifndef PROJECT_INCLUDE_FORMATS_FOR_OUTPUT_H_
#define PROJECT_INCLUDE_FORMATS_FOR_OUTPUT_H_

#include "data_and_recording.h"

#define OUTPUT_CRED_FORMAT "%-12d%-*s%-*s%-*s%*s%12.2f%12.2f%12.2f\n"
#define OUTPUT_TRANS_FORMAT "%-3d%-6.2f\n"

#define FORMAT_STRING_MAX_SIZE 10

enum formats {
    PERSON_FORMAT = PERSON - 9, ADDRESS_FORMAT = ADDRESS - 14, PHONE_FORMAT = PHONE + 5
};

#endif  // PROJECT_INCLUDE_FORMATS_FOR_OUTPUT_H_
