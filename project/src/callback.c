#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "mail_parser.h"

bool check_boundary(char *str, int i);
int find_boundary_val(char *str, char boundary[]);
void fill_boundary(char *str, char boundary[], int *i);
int len_dest_str(char *str);

int callback(char *str, mod_t mod) {
    static char from_str[OUTPUT_SIZE];
    static char to_str[OUTPUT_SIZE];
    static char date_str[OUTPUT_SIZE];

    static int p_count;

    static int write_str_mod = H_OTHER;

    switch (mod) {
        case STR: {
            static char boundary[BOUNDARY_SIZE];

            switch (write_str_mod) {
                case H_FROM: {
                    int len = len_dest_str(from_str);
                    strncat(from_str, str, OUTPUT_SIZE - len);
                    break;
                }
                case H_TO: {
                    int len = len_dest_str(to_str);
                    strncat(to_str, str, OUTPUT_SIZE - len);
                    break;
                }
                case H_DATE: {
                    int len = len_dest_str(date_str);
                    strncat(date_str, str, OUTPUT_SIZE - len);
                    break;
                }
                case H_CONTENT_TYPE: {
                    int return_code = find_boundary_val(str, boundary);
                    if (return_code == NO_MULTYPART) {
                        write_str_mod = H_OTHER;
                    } else if (return_code != 0) {
                        return 1;
                    }
                    break;
                }
                case BEGIN_OF_BODY: {
                    if (strcmp(boundary, "\0") == 0) {
                        p_count = 1;
                    } else if (strcmp(boundary, str) == 0) {
                        ++p_count;
                    }
                    break;
                }
                default: {
                    break;
                }
            }
            break;
        }
        case END: {
            printf("%s|%s|%s|%d\n", from_str, to_str, date_str, p_count);
            break;
        }
        default: {
            if (write_str_mod != BEGIN_OF_BODY) {  // не учитываем заголовки внутри тела
                write_str_mod = mod;
            }
        }
    }
    return 0;
}

int len_dest_str(char *str) {
    int count = 0;
    for (; str[count] != '\0'; ++count) {}
    if (count != 0) {
        str[count] = ' ';
        str[count + 1] = '\0';
    }
    return count;
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
