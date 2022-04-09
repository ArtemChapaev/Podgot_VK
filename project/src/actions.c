#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "mail_parser.h"

int valid_h(char *header, callback_t callback) {
    char *correct_header = calloc((sizeof header) + 1, sizeof(char));
    int i = 0;

    for (; header[i] != '\0'; ++i) {
        correct_header[i] = tolower(header[i]);
    }

    correct_header[i] = '\0';
    //printf("correct header - %s\n",correct_header);

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
    return 0;
}


int str_check(char *header, callback_t callback) { // rename, bcs part_count
    callback(header, STR);
    return 0;
}

int part_begin(char *header, callback_t callback) {
    callback(header, EMPTY_STR);
    return 0;
}

int finish(char *header, callback_t callback) {
    callback(header, END);
    return 0;
}
