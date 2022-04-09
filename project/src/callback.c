#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "mail_parser.h"

int callback(char *str, int mod) {
    /*static char *from_str = malloc(OUTPUT_SIZE);
    static char *to_str = malloc(OUTPUT_SIZE);
    static char *date_str = malloc(OUTPUT_SIZE);*/

    static char bound[BUF_SIZE];
    static int p_count;

    static int write_str_mod = H_OTHER;

    if (mod == STR) {
        switch (write_str_mod) {
            case H_FROM: {
                printf("from - %s\n", str);
                //from_str += str;
                break;
            }
            case H_TO: {
                //to_str += str;
                printf("to - %s\n", str);
                break;
            }
            case H_DATE: {
                //date_str += str;
                printf("date - %s\n", str);
                break;
            }
            case H_CONTENT_TYPE: {
//                printf("\nCONTENT_TYPE\n");
//                printf("\n%s\n", str);
                char *buf = malloc(BUF_SIZE);
                int j = 0;

                for (int i = 0; str[i] != '\0'; i++) {
                    if (str[i] == '/') {
                        if (strcmp("multipart", buf) != 0) {
                            break;
                        }
                    } else if (str[i] == '=') {
                        if (str[++i] == '"'){
                            ++i;
                        }

                        int index = 0;
                        for (; index < 2; ++index) {
                            bound[index] = '-';
                        }
                        while (str[i] != '"' && str[i] != '\0') {
                            bound[index++] = str[i++];
                        }
                        bound[index] = '\0';
                        //printf("boundary - %s\n\n", bound);
                    } else {
                        buf[j++] = str[i];
                    }
                }
                free(buf);
                break;
            }
            case H_OTHER: {
                break;
            }
            case PART: {
                //printf("%s\n", str);
                if (strcmp(bound, "") == 0) {
                    p_count = 1;
                } else if (strcmp(bound, str) == 0) {
                    ++p_count;
                    //printf("part count = %d\n", p_count);
                }
                break;
            }
            default: {
            }
        }
    } else if (mod == EMPTY_STR) {
        write_str_mod = PART;
        //printf("\nwrite_str_mod = PART\n");
    } else if (mod == END) {
        printf("part = %d\n", p_count);
    } else {
        if (write_str_mod != PART) {
            write_str_mod = mod;
            //printf("change mod, write_mod = %d\n", write_str_mod);
        }
    }
    return 0;
}
