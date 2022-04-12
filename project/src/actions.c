#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "mail_parser.h"

int valid_h(char* header, callback_t callback, mod_t* mod) {
    size_t size = strlen(header) + 1;
    char *correct_header = malloc(size);
    if (correct_header == NULL) {
        return ERR_MEMORY;
    }
    int i = 0;

    for (; header[i] != '\0'; ++i) {
        correct_header[i] = tolower(header[i]);
    }
    correct_header[i] = '\0';

    if (strcmp(correct_header, FROM) == 0) {
        callback(NULL, H_FROM, mod);
    } else if (strcmp(correct_header, TO) == 0) {
        callback(NULL, H_TO, mod);
    } else if (strcmp(correct_header, DATE) == 0) {
        callback(NULL, H_DATE, mod);
    } else if (strcmp(correct_header, CONTENT_TYPE) == 0) {
        callback(NULL, H_CONTENT_TYPE, mod);
    } else {
        callback(NULL, H_OTHER, mod);
    }
    free(correct_header);
    return 0;
}


int str_check(char *str, callback_t callback, mod_t *mod) {
    callback(str, STR, mod);
    return 0;
}

int part_begin(char *str, callback_t callback, mod_t *mod) {
    callback(str, BODY, mod);
    return 0;
}

int finish(char *str, callback_t callback, mod_t *mod) {
    callback(str, END, mod);
    return 0;
}
