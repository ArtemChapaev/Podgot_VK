#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils_for_tests.h"
#include "utils.h"
#include "credentials_recording.h"

int test_write_file();

int main() {
    int return_code = test_write_file();

    if (return_code != 0) {
        printf(ERROR_MESSAGE);
    } else {
        printf(CORRECT_END_MESSAGE);
    }

    return return_code;
}

int test_write_file() {
    // пункт 1: запись в файл
    data_t expected_data = {
            111, "Name_11", "Surname_11", "Moscow",
            "88005353535", 111, 111, 111};

    FILE *p_write_file = fopen(UNIT_TEST_FILE, "w");
    if (p_write_file == NULL) {
        return ERR_NO_FILE_OPENED;
    }

    int return_code;
    return_code = write_to_file_credentials(p_write_file, expected_data);
    fclose(p_write_file);

    // пункт 2: проверка правильности записи
    if (return_code == 0) {
        return ERR_WRONG_COMPARING;
    }
    return 0;
}
