#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "mail_parser.h"

bool check_boundary(char *str, int i);
int find_boundary_val(char *str, char boundary[]);
void fill_boundary(char *str, char boundary[], int *i);

int callback(char *str, mod_t mod, mod_t *output_mod) {
    static int write_str_mod = H_OTHER;

    switch (mod) {
        case STR: {
            static char boundary[BOUNDARY_SIZE];

            switch (write_str_mod) {
                case H_FROM: {
                    *output_mod = H_FROM;
                    break;
                }
                case H_TO: {
                    *output_mod = H_TO;
                    break;
                }
                case H_DATE: {
                    *output_mod = H_DATE;
                    break;
                }
                case H_CONTENT_TYPE: {
                    int return_code = find_boundary_val(str, boundary);
                    if (return_code == NO_MULTYPART) {
                        write_str_mod = H_OTHER;
                    } else if (return_code != 0) {
                        return ERR_MEMORY;
                    }
                    *output_mod = END;
                    break;
                }
                case BODY: {
                    if (strcmp(boundary, "\0") == 0) {
                        *output_mod = NO_MULTYPART;
                    } else if (strcmp(boundary, str) == 0) {
                        *output_mod = BODY;
                    }
                }
            }
            break;
        }
        default: {
            if (write_str_mod != BODY) {  // не учитываем заголовки внутри тела
                write_str_mod = mod;
            }
            *output_mod = END;
        }
    }
    return 0;
}

bool check_boundary(char *str, int i) {
    char *buf = malloc(BOUNDARY_LEN);
    if (buf == NULL) {
        return false;
    }

    int g = 0;
    if (i < BOUNDARY_LEN - 1) {
        free(buf);
        return false;
    }
    if (i > BOUNDARY_LEN - 1 && str[i - BOUNDARY_LEN] != ' ' && str[i - BOUNDARY_LEN] != ';') {
        free(buf);
        return false;
    }

    for (int k = i - BOUNDARY_LEN + 1; k < i; ++k) {
        buf[g++] = tolower(str[k]);
    }
    buf[g] = '\0';

    if (strcmp("boundary", buf) != 0) {
        free(buf);
        return false;
    }

    free(buf);
    return true;
}


void fill_boundary(char *str, char boundary[], int *i) {
    int index = 0;
    for (; index < 2; ++index) {
        boundary[index] = '-';
    }

    while (str[*i] != '"' && str[*i] != '\0' && str[*i] != ' ') {
        boundary[index++] = str[(*i)++];
    }
    boundary[index] = '\0';
}

int find_boundary_val(char *str, char boundary[]) {
    bool is_type = true;
    int j = 0;

    char *buf = malloc(BUF_SIZE);
    if (buf == NULL) {
        return ERR_MEMORY;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/') {
            is_type = false;
            buf[j] = '\0';
            if (strcmp("multipart", buf) != 0) {    // если это не multipart,
                free(buf);                          // то boundary пустой
                return NO_MULTYPART;
            }
        } else if (str[i] == '=') {
            if (!check_boundary(str, i)) {
                continue;
            }

            ++i;
            if (str[i] == '"') {
                ++i;
            }

            fill_boundary(str, boundary, &i);

        } else if (is_type) {
            buf[j++] = tolower(str[i]);
        }
    }

    free(buf);
    return 0;
}
