#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "mail_parser.h"

int valid_h(char* header, callback_t callback) {
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
        callback(NULL, H_FROM);
    } else if (strcmp(correct_header, TO) == 0) {
        callback(NULL, H_TO);
    } else if (strcmp(correct_header, DATE) == 0) {
        callback(NULL, H_DATE);
    } else if (strcmp(correct_header, CONTENT_TYPE) == 0) {
        callback(NULL, H_CONTENT_TYPE);
    } else {
        callback(NULL, H_OTHER);
    }
    free(correct_header);
    return 0;
}


int str_check(char *str, callback_t callback) {
    callback(str, STR);
    return 0;
}

int part_begin(char *str, callback_t callback) {
    callback(str, BEGIN_OF_BODY);
    return 0;
}

int finish(char *str, callback_t callback) {
    callback(str, END);
    return 0;
}
