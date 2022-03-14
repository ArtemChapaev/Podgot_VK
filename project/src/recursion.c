#include "utils.h"

void numbers_to_one(int num, int output_num) {
    if (output_num == num) {		// условие завершения рекурсии
	printf("%d\n", output_num);
	return;
    } else if (num > 1) {		// продолжение рекурсии при num > 1
	printf("%d ", output_num);
	numbers_to_one(num, output_num + 1);
    } else {				// продолжение рекурсии при num < 1
	printf("%d ", output_num);
	numbers_to_one(num, output_num - 1);
    }
}

