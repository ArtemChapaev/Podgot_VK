#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "mail_parser.h"
#include "actions.h"

typedef int (*action_t)(char *str, callback_t callback);

typedef enum {
    L_HNAME,
    L_STR,
    L_SPACE_STR,
    L_EMPTY_STR,
    L_EOF,
    L_COUNT,
    L_ERR
} lexem_t;

typedef enum {
    S_BEGIN,
    S_HNAME,
    S_HVALUE,
    S_HEND,
    S_PART,
    S_END,
    S_COUNT,
    S_ERR
} state_t;

typedef struct {
    state_t state;
    action_t action;
} rule_t;

static char *get_lexem(FILE *file, lexem_t *lexem);

void check_next_sym(FILE *file, char ch);

void str_translate(lexem_t *lexem, int j, char *buf);

static rule_t transitions[S_COUNT][L_COUNT] = {
//                  L_HNAME                 L_STR                   L_SPACE_STR                 L_EMPTY_STR         L_EOF

/*S_BEGIN*/         {{S_HNAME, valid_h},    {S_ERR, NULL},          {S_ERR, NULL},              {S_ERR, NULL},          {S_ERR, NULL}},
/*S_HNAME*/         {{S_ERR, NULL},         {S_HVALUE, str_check},  {S_ERR, NULL},              {S_ERR, NULL},          {S_ERR, NULL}},
/*S_HVALUE*/        {{S_HNAME, valid_h},    {S_ERR, NULL},          {S_VALUE, str_check},       {S_HEND, part_begin},   {S_ERR, NULL }},
/*S_HEND*/          {{S_PART, NULL},        {S_PART, str_check},    {S_ERR, NULL},              {S_HEND, part_begin},   {S_END, finish }},

/*S_PART*/          {{S_PART, NULL},        {S_PART, str_check},    {S_PART, str_check},        {S_PART, NULL},         {S_END, finish }},
/*S_END*/           {{S_ERR, NULL},         {S_ERR, NULL},          {S_ERR, NULL},              {S_ERR, NULL},          {S_ERR, NULL}}
};

char *mail_parser(FILE *eml_file) {
    state_t state = S_BEGIN;
    lexem_t lexem;
    char *str = get_lexem(eml_file, &lexem);
    while (true) {
        rule_t rule = transitions[state][lexem];

        if (rule.state == S_ERR) {
            free(str);
            return NULL;
        }
        //printf("lexem = %d - %s\n", lexem, str);
        if (rule.action != NULL) {
            int return_code = rule.action(str, callback);
            if (return_code != 0) {
                free(str);
                return NULL;
            }
        }
        state = rule.state;
        free(str);
        if (lexem == L_EOF) {
            //printf("EOF\n");
            break;
        } else {
            str = get_lexem(eml_file, &lexem);
        }
    }
    return NULL;
}

static char *get_lexem(FILE *file, lexem_t *lexem) {
    static bool is_header_value = false;

    char *buf = malloc(BUF_SIZE);
    int j = 0;
    char ch;

    while ((ch = fgetc(file)) != EOF) {
        switch (ch) {
            case '\n': {
                check_next_sym(file, '\r');

                str_translate(lexem, j, buf);
                is_header_value = false;
                return buf;
            }
            case '\r': {
                check_next_sym(file, '\n');

                str_translate(lexem, j, buf);
                is_header_value = false;
                return buf;
            }
            case ':': {
                if (is_header_value) { // возможно наличие ':' в строке со временем
                    buf[j++] = ch;
                    break;
                } else {
                    is_header_value = true;
                    buf[j] = '\0';
                    *lexem = L_HNAME;
                    return buf;
                }
            }
            case ' ': {
                if (is_header_value && j == 0) { // обрабатывается пробел после имени заголовка
                    break;
                } else if (j == 0) {
                    *lexem = L_SPACE_STR;

                    do {
                        ch = fgetc(file);
                    } while (isspace(ch));
                    buf[j++] = ch;

                    // fgets, но без считывания перевода строки
                    for (; ((ch = fgetc(file)) != '\n' && ch != '\r') && (j < BUF_SIZE - 1); ++j) {
                        buf[j] = ch;
                    }
                    if (ch == '\n') {
                        check_next_sym(file, '\r');
                    }
                    if (ch == '\r') {
                        check_next_sym(file, '\n');
                    }

                    buf[j] = '\0';
                    return buf;
                } else {
                    buf[j++] = ch;
                    break;
                }
            }
            default: {
                buf[j++] = ch;
            }
        }
    }
    *lexem = L_EOF;
    free(buf);
    return NULL;
}

void check_next_sym(FILE *file, char ch) {
    char next = fgetc(file);
    if (next != ch) {
        ungetc(next, file);
    }
}

void str_translate(lexem_t *lexem, int j, char *buf) {
    if (j == 0) {
        *lexem = L_EMPTY_STR;
    } else {
        *lexem = L_STR;
    }
    buf[j] = '\0';
    return;
}
