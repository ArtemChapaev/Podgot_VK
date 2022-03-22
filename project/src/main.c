#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "credentials_recording.h"
#include "transaction_recording.h"
#include "base_updating.h"
#include "helper.h"


int main(void) {
    invocation_choice();

    int choice = 0;
    while (scanf("%d", &choice) == 1) {
        switch (choice) {
            case ENT_DATA_CLIENT: {
                FILE *p_credentials_file;
                p_credentials_file = fopen("record.dat", "r+");

                if (p_credentials_file == NULL) {
                    printf("Not access to %s", "record.dat");
                    return ERR_WRONG_FILE;

                } else {
                    write_credentials(p_credentials_file);
                    fclose(p_credentials_file);
                }
                break;
            }

            case ENT_DATA_TRANS: {
                FILE *p_transaction_file = fopen("transaction.dat", "r+");

                if (p_transaction_file == NULL) {
                    printf("Not access to %s", "transaction.dat");
                    return ERR_WRONG_FILE;

                } else {
                    write_transaction(p_transaction_file);
                    fclose(p_transaction_file);
                }
                break;
            }

            case UPD_BASE: {
                FILE *p_credentials_file = fopen("record.dat", "r");
                FILE *p_transaction_file = fopen("transaction.dat", "r");
                FILE *p_update_base_file = fopen("blackrecord.dat", "w");

                if (p_credentials_file == NULL || p_transaction_file == NULL || p_update_base_file == NULL) {
                    printf("Not access to %s, %s, %s", "record.dat", "transaction.dat", "blackrecord.dat");
                    return ERR_WRONG_FILE;

                } else {
                    update_base(p_credentials_file, p_transaction_file, p_update_base_file);

                    fclose(p_credentials_file);
                    fclose(p_transaction_file);
                    fclose(p_update_base_file);
                }
                break;
            }

            default:
                printf("Error, invalid choice\n");
                return ERR_WRONG_CHOICE;
        }
        invocation_choice();
    }
    return 0;
}
