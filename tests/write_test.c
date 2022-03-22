#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../project/include/utils.h"
#include "../project/include/credentials_recording.h"

int test_write_file();

int main() {
    int return_code = test_write_file();
    if (return_code != 0) {
        printf("%s\n", "ERROR!");
        return 1;
    } else {
        printf("%s\n", "Correct ending");
        return 0;
    }
}

int test_write_file() {
    char *filename = "write_test.dat";

    // пункт 1: запись в файл
    data_t expected_data = {
            111, "Name_11", "Surname_11", "Moscow", "88005353535",
            111, 111, 111};

    FILE *p_write_file = fopen(filename, "w");
    int return_code;

    if (p_write_file == NULL) {
        return -1;

    } else {
        return_code = write_to_file_credentials(p_write_file, expected_data);
    }
    fclose(p_write_file);

    // пункт 2: проверка правильности записи
    if (return_code == 0) {
        return 1;
    } else {
        return 0;
    }
}
