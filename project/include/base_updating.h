#ifndef PROJECT_INCLUDE_BASE_UPDATING_H_
#define PROJECT_INCLUDE_BASE_UPDATING_H_

#include <stdio.h>
#include "utils.h"

void update_base(FILE *const p_credentials_file, FILE *const p_transaction_file,
                 FILE *const p_update_base_file);

int read_credentials_from_file(FILE *const p_credentials_file, data_t *client_data);  // нужна для тестов

#endif  // PROJECT_INCLUDE_BASE_UPDATING_H_
