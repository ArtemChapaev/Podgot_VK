#ifndef PROJECT_INCLUDE_ACTIONS_H_
#define PROJECT_INCLUDE_ACTIONS_H_

#include "mail_parser.h"

int valid_h(char *header, callback_t callback);
int str_check(char *str, callback_t callback);
int part_begin(char *str, callback_t callback);
int finish(char *str, callback_t callback);

#endif  // PROJECT_INCLUDE_ACTIONS_H_
