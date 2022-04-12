#include <stdlib.h>
#include <stdio.h>

#include "mail_parser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        printf("To little argc\n");
        return 0;
    }

    const char *path_to_eml = argv[1];

    FILE *eml_file = fopen(path_to_eml, "r");
    if (eml_file == NULL) {
        printf("ERROR opening\n");
        return 0;
    }

    if (mail_parser(eml_file) != 0) {
        printf("Error parser\n");
        return 0;
    }
    fclose(eml_file);
    return 0;
}
