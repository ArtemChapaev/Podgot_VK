#ifndef PODGOT_VK_MAIL_PARSER_H
#define PODGOT_VK_MAIL_PARSER_H

#include <stdbool.h>

#define H_FROM "from"
#define H_TO "to"
#define H_DATE "date"
#define H_CONTENT_TYPE "content-type"

char *mail_parser(FILE *eml_file);

#endif //PODGOT_VK_MAIL_PARSER_H
