#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>

/*
 * Comparing two numbers written in index form like 2^(11) and 3^(7) is not
 * difficult, as any calculator would confirm that 2^(11) = 2048 < 3^(7) = 2187.
 *
 * However, confirming that 632382^(518061) > 519432^(525806) would be much
 * more difficult, as both numbers contain over three million digits.
 *
 * Using base_exp.txt (right click and 'Save Link/Target As...'), a 22K text
 * file containing one thousand lines with a base/exponent pair on each line,
 * determine which line number has the greatest numerical value.
 *
 * NOTE: The first two lines in the file represent the numbers in the example
 * given above.
 */

mpz_t currentMax;
int currentMaxLine = 0;

void calculate(int lineNumber, const char *baseString, const char *exponentString)
{
    mpz_t result, base, exponent;
    // Initialize
    mpz_init_set_str(result, baseString, 10);
    mpz_init_set_str(base, baseString, 10);
    mpz_init_set_str(exponent, exponentString, 10);
    // Calculate
    while (mpz_cmp_ui(exponent, 1) > 0)
    {
        mpz_mul(result, result, base);
        mpz_sub_ui(exponent, exponent, 1);
    }
#if 1
    // Output
    printf("%d: %s^%s=", lineNumber, baseString, exponentString);
    mpz_out_str(stdout, 10, result);
    printf("\n");
#endif
    // Check win
    if (mpz_cmp(result, currentMax) > 0)
    {
        printf("New max, line %d\n", lineNumber);
        mpz_set(currentMax, result);
        currentMaxLine = lineNumber;
    }
    // Clean up
    mpz_clear(result);
    mpz_clear(base);
    mpz_clear(exponent);
}

int main(int argc, char **argv)
{
    char line[80];
    char *p;
    int lineNumber = 0;
    FILE *f = fopen("base_exp.txt", "r");
    mpz_init(currentMax);
#if 0
    calculate(1, "2", "11");
    calculate(2, "3", "7");
#else
    while (fgets(line, sizeof(line) - 1, f))
    {
        lineNumber++;
        line[sizeof(line) - 1] = 0;
        for (char *c = line; *c; c++)
            if (*c < ' ')
                *c = 0;
        p = strchr(line, ',');
        if (!p)
        {
            printf("Comma not found!\n");
            return 1;
        }
        *p = 0;
        p++;
        printf("%s^%s\n", line, p);
        calculate(lineNumber, line, p);
    }
#endif
    return 0;
}
