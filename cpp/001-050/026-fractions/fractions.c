#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <math.h>
//#include <ctype.h>
//#include <gmp.h>
/*
 *
 */
#define BUFFER_SIZE 160

void longDivisionInverse(unsigned int denom, char *buffer, int len)
{
    char *orig = buffer;
    unsigned int num = 1;
    len -= 3;
    *buffer++ = '0';
    *buffer++ = '.';
    while (len > 0)
    {
        num *= 10;
        //printf("     %s\n", orig);
        while ((num < denom) && (len > 0))
        {
            len--;
            *buffer++ = '0';
            num *= 10;
            //printf("%d ) %d\n", denom, num);
        }
        if (len <= 0)
            break;
        //printf("%d %d\n", num / denom, num % denom);
        *buffer++ = num / denom + '0';
        len--;
        num %= denom;
    }
    *buffer++ = '\0';
}

int checkRepeat(const char *s, int max)
{
    const char *p = s + 10;
    while (max)
    {
        char match = 1;
        for (int i = 0; (i < max) && match; i++)
            if (*(p + i) != *(p + i +max))
                match = 0;
        if (match)
            return max;
        max--;
    }
    return max;
}

const char *strrstrBrian(const char *string, const char *find)
{
    size_t stringlen, findlen;
    const char *cp;

    findlen = strlen(find);
    stringlen = strlen(string) - 1;
    if (findlen > stringlen)
        return NULL;

    for (cp = string + stringlen - findlen; cp >= string; cp--)
        if (strncmp(cp, find, findlen) == 0)
            return cp;
    return NULL;
}

int checkRepeat2(const char *s, int max)
{
    const char *end = s + strlen(s) - 20;
    const char *start = strrstrBrian(s, end);
    if (start)
    {
        if (strncmp(start - (end - start), end, 20) == 0)
            return end - start;
    }
    return 0;
}

void output()
{
    char buffer[BUFFER_SIZE];
    FILE *f;
    f = fopen("output.txt", "w");
    for (int n = 2; n < 1000; n++)
    {
        int max;
        longDivisionInverse(n, buffer, BUFFER_SIZE - 10);
        max = checkRepeat2(buffer, 25);
        printf("%2d: 1/%03d = %s\n", max, n, buffer);
        fprintf(f, "%2d: 1/%03d = %s\n", max, n, buffer);
    }
    fclose(f);
}

int main(int argc, char **argv)
{
    output();
    return 0;
}
