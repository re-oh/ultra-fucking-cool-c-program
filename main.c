#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct num_char {
    char* num1;
    char* num2;
};

void long_multiply(char *num1, char *num2, char *result) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int result_size = len1 + len2;

    for (int i = 0; i < result_size; i++) {
        result[i] = '0';
    }
    result[result_size] = '\0';

    for (int i = len1 - 1; i >= 0; i--) {
        int carry = 0;
        int digit1 = num1[i] - '0';

        for (int j = len2 - 1; j >= 0; j--) {
            int digit2 = num2[j] - '0';
            int product = digit1 * digit2;
            int sum = (result[i + j + 1] - '0') + product + carry;
            result[i + j + 1] = (sum % 10) + '0';
            carry = sum / 10;
        }
        result[i] += carry;
    }

    int start = 0;
    while (start < result_size - 1 && result[start] == '0') {
        start++;
    }

    if (start > 0) {
        memmove(result, result + start, result_size - start + 1);
    }
}

int main() {
    struct num_char numbers;
    numbers.num1 = NULL;
    numbers.num2 = NULL;
    size_t capacity1 = 0, capacity2 = 0;
    size_t length1 = 0, length2 = 0;
    int c;
    int space_found = 0;

    while ((c = getchar()) != '\n' && c != EOF) {
        if (isspace(c)) {
            if (space_found) break;
            space_found = 1;
            numbers.num1 = realloc(numbers.num1, (length1 + 1) * sizeof(char));
            numbers.num1[length1] = '\0';
            continue;
        }

        if (!isdigit(c)) {
            printf("u cant calculate letters u dumb fuck\n");
            free(numbers.num1);
            free(numbers.num2);
            return 1;
        }

        if (!space_found) {
            if (length1 >= capacity1) {
                capacity1 = capacity1 ? capacity1 * 2 : 2;
                numbers.num1 = realloc(numbers.num1, capacity1 * sizeof(char));
            }
            numbers.num1[length1++] = c;
        } else {
            if (length2 >= capacity2) {
                capacity2 = capacity2 ? capacity2 * 2 : 2;
                numbers.num2 = realloc(numbers.num2, capacity2 * sizeof(char));
            }
            numbers.num2[length2++] = c;
        }
    }

    if (!space_found || length1 == 0 || length2 == 0) {
        printf("input should be 2 numbers separated by spaces like: 213 213123\n");
        free(numbers.num1);
        free(numbers.num2);
        return 1;
    }

    numbers.num2 = realloc(numbers.num2, (length2 + 1) * sizeof(char));
    numbers.num2[length2] = '\0';

    char* product = malloc((length1 + length2 + 1) * sizeof(char));
    long_multiply(numbers.num1, numbers.num2, product);
    printf("Product: %s\n", product);

    free(numbers.num1);
    free(numbers.num2);
    free(product);

    return 0;
}