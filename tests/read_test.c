#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../project/include/utils.h"
#include "../project/include/base_updating.h"

int test_read_file();

int main() {
    int return_code = test_read_file();
    if (return_code != 0) {
        printf("%s\n", "ERROR!");
        return 1;
    } else {
        printf("%s\n", "Correct ending");
        return 0;
    }
}

int test_read_file() {
    char *filename = "read_test.dat";

    // пункт 1: чтение данных из файла
    data_t got_data;
    FILE *p_read_file = fopen(filename, "r");

    if (p_read_file == NULL) {
        return -1;

    } else {
        int return_code = read_credentials_from_file(p_read_file, &got_data);
        if (return_code != 0) {
            return -2;
        }
        fclose(p_read_file);
    }

    // пункт 2: проверка правильности чтения
    if (got_data.number == 0 || got_data.indebtedness == 0 ||
        got_data.credit_limit == 0 || got_data.cash_payments == 0 ||
        got_data.name == NULL || got_data.surname == NULL ||
        got_data.address == NULL || got_data.tel_number == NULL) {
        return 1;

    } else {
        return 0;
    }
}
