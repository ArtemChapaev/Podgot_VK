#include <stdio.h>
#include <stdlib.h>
#include "../include/utils.h"

int read_credentials_from_file(FILE *const p_credentials_file, data_t *client_data);

int read_transaction_from_file(FILE *const p_transaction_file, data_t *transfer);

void write_updates_to_file(FILE *const p_update_base_file, data_t client_data);

void update_base(FILE *const p_credentials_file, FILE *const p_transaction_file,
                 FILE *const p_update_base_file) {
    data_t client_data;
    int return_code = read_credentials_from_file(p_credentials_file, &client_data);

    while (return_code == 0) {
        data_t transfer;
        return_code = read_transaction_from_file(p_transaction_file, &transfer);
        while (return_code == 0) {
            if (client_data.number == transfer.number && transfer.cash_payments != 0) {
                client_data.credit_limit += transfer.cash_payments;
            }

            return_code = read_transaction_from_file(p_transaction_file, &transfer);
        }
        write_updates_to_file(p_update_base_file, client_data);

        rewind(p_transaction_file);

        return_code = read_credentials_from_file(p_credentials_file, &client_data);
    }
}

int read_credentials_from_file(FILE *const p_credentials_file, data_t *client_data) {
    int return_code = fscanf(p_credentials_file, "%d", &client_data->number);
    if (return_code != 1) {
        return 1;
    }

    char format_person[FORMAT_STRING_MAX_SIZE];
    snprintf(format_person, FORMAT_STRING_MAX_SIZE, "%%%ds", PERSON - 1);

    return_code = fscanf(p_credentials_file, format_person, client_data->name);
    if (return_code != 1) {
        return 1;
    }

    return_code = fscanf(p_credentials_file, format_person, client_data->surname);
    if (return_code != 1) {
        return 1;
    }

    char format_address[FORMAT_STRING_MAX_SIZE];
    snprintf(format_address, FORMAT_STRING_MAX_SIZE, "%%%ds", ADDRESS - 1);

    return_code = fscanf(p_credentials_file, format_address, client_data->address);
    if (return_code != 1) {
        return 1;
    }

    char format_tel_num[FORMAT_STRING_MAX_SIZE];
    snprintf(format_tel_num, FORMAT_STRING_MAX_SIZE, "%%%ds", PHONE - 1);

    return_code = fscanf(p_credentials_file, format_tel_num, client_data->tel_number);
    if (return_code != 1) {
        return 1;
    }

    return_code = fscanf(p_credentials_file, "%lf", &client_data->indebtedness);
    if (return_code != 1) {
        return 1;
    }

    return_code = fscanf(p_credentials_file, "%lf", &client_data->credit_limit);
    if (return_code != 1) {
        return 1;
    }

    return_code = fscanf(p_credentials_file, "%lf", &client_data->cash_payments);
    if (return_code != 1) {
        return 1;
    } else {
        return 0;
    }
}

int read_transaction_from_file(FILE *const p_transaction_file, data_t *transfer) {
    int return_code = fscanf(p_transaction_file, "%d", &transfer->number);
    if (return_code != 1) {
        return 1;
    }

    return_code = fscanf(p_transaction_file, "%lf", &transfer->cash_payments);
    if (return_code != 1) {
        return 1;
    } else {
        return 0;
    }
}

void write_updates_to_file(FILE *const p_update_base_file, data_t client_data) {
    fprintf(p_update_base_file, "%-12d%-*s%-*s%-*s%*s%12.2f%12.2f%12.2f\n",
            client_data.number, PERSON - 9, client_data.name, PERSON - 9, client_data.surname,
            ADDRESS - 14, client_data.address, PHONE + 5, client_data.tel_number,
            client_data.indebtedness, client_data.credit_limit, client_data.cash_payments);
}

