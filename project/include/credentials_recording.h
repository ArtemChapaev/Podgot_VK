#ifndef PROJECT_INCLUDE_CREDENTIALS_RECORDING_H_
#define PROJECT_INCLUDE_CREDENTIALS_RECORDING_H_

#include <stdio.h>
#include "utils.h"

void write_credentials(FILE *const p_record_file);

int write_to_file_credentials(FILE *const p_credentials_file, data_t client_data);  // нужна для тестов

#endif  // PROJECT_INCLUDE_CREDENTIALS_RECORDING_H_
