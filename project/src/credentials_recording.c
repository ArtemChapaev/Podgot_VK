#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "utils_for_functions.h"

void invocation_enter_credentials();

int enter_credentials(data_t *client_data);

int write_to_file_credentials(FILE *const p_credentials_file, data_t client_data);

void write_credentials(FILE *const p_credentials_file) {
    invocation_enter_credentials();

    data_t client_data;
    int return_code = enter_credentials(&client_data);

    while (return_code == 0) {
        write_to_file_credentials(p_credentials_file, client_data);
        invocation_enter_credentials();
        return_code = enter_credentials(&client_data);
    }
}

void invocation_enter_credentials() {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
           "1 Number account: ",
           "2 Client name: ",
           "3 Surname: ",
           "4 Address client: ",
           "5 Client tel_num: ",
           "6 Client indebtedness: ",
           "7 Client credit limit: ",
           "8 Client cash payments:");
}

int enter_credentials(data_t *client_data) {
    int return_code = scanf("%d", &client_data->number);
    if (return_code != 1) {
        return ERR_WRONG_INPUT;
    }

    char format_person[FORMAT_STRING_MAX_SIZE];
    snprintf(format_person, FORMAT_STRING_MAX_SIZE, "%%%ds", PERSON - 1);

    return_code = scanf(format_person, client_data->name);
    if (return_code != 1) {
        return ERR_WRONG_INPUT;
    }

    return_code = scanf(format_person, client_data->surname);
    if (return_code != 1) {
        return ERR_WRONG_INPUT;
    }

    char format_address[FORMAT_STRING_MAX_SIZE];
    snprintf(format_address, FORMAT_STRING_MAX_SIZE, "%%%ds", ADDRESS - 1);

    return_code = scanf(format_address, client_data->address);
    if (return_code != 1) {
        return ERR_WRONG_INPUT;
    }

    char format_tel_num[FORMAT_STRING_MAX_SIZE];
    snprintf(format_tel_num, FORMAT_STRING_MAX_SIZE, "%%%ds", PHONE - 1);

    return_code = scanf(format_tel_num, client_data->tel_number);
    if (return_code != 1) {
        return ERR_WRONG_INPUT;
    }

    return_code = scanf("%lf", &client_data->indebtedness);
    if (return_code != 1) {
        return ERR_WRONG_INPUT;
    }

    return_code = scanf("%lf", &client_data->credit_limit);
    if (return_code != 1) {
        return ERR_WRONG_INPUT;
    }

    return_code = scanf("%lf", &client_data->cash_payments);
    if (return_code != 1) {
        return ERR_WRONG_INPUT;
    } else {
        return 0;
    }
}

int write_to_file_credentials(FILE *const p_credentials_file, data_t client_data) {
    int return_code = fprintf(p_credentials_file, OUTPUT_CRED_FORMAT,
                              client_data.number, PERSON_FORMAT, client_data.name, PERSON_FORMAT,
                              client_data.surname, ADDRESS_FORMAT, client_data.address, PHONE_FORMAT,
                              client_data.tel_number, client_data.indebtedness,
                              client_data.credit_limit, client_data.cash_payments);
    return return_code;
}
