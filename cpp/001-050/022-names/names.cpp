#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <gmp.h>

unsigned int nameScore(const char *name)
{
    unsigned int result = 0;
    for (const char *c = name; *c; c++)
    {
        if (*c < ' ')
            return result;
        if (!isalpha(*c))
        {
            printf("Not a name! %s\n", name);
            exit(1);
        }
        result += toupper(*c) - 'A' + 1;
    }
    return result;
}

void parseFile(const char *filename)
{
    int ch;
    FILE *in = fopen(filename, "r");
    FILE *out = fopen("temp1.txt", "w");
    while ((ch = fgetc(in)) >= 0)
    {
        if (ch == '"')
            continue;
        if (ch == ',')
            fputc('\n', out);
        else
            fputc(ch, out);
    }
    fputc('\n', out);
    fclose(in);
    fclose(out);
}

int main(int argc, char **argv)
{
    int lineNumber = 1;
    mpz_t sum;
    mpz_t lineTotal;
    mpz_init_set_ui(sum, 0);
    mpz_init(lineTotal);
    FILE *f;
    char line[80];
    parseFile("names.txt");
    system("sort temp1.txt > temp2.txt");
    f = fopen("temp2.txt", "r");
    while (fgets(line, sizeof(line), f) != NULL)
    {
        mpz_set_ui(lineTotal, nameScore(line));
        mpz_mul_ui(lineTotal, lineTotal, lineNumber);
        mpz_add(sum, sum, lineTotal);
        lineNumber++;
    }
    printf("%s\n", mpz_get_str(NULL, 10, sum));
    return 0;
}
