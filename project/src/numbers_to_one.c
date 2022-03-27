#include <stdio.h>
#include <stdlib.h>

void numbers_to_one(int num, int output_num) {
    printf("%d", output_num);

    if (output_num == num) {
        putchar('\n');
        return;
    } else {
        putchar(' ');

        if (num > 1) {
            numbers_to_one(num, output_num + 1);
        } else {
            numbers_to_one(num, output_num - 1);
        }
    }
}
