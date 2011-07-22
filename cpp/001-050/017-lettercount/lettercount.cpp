#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int letterCount(int number) 
{
    if ((number >= 0) && (number <= 9))
        switch(number) 
        {
            case 0: return 0;
            case 1: return 3; // one
            case 2: return 3; // two
            case 3: return 5; // three
            case 4: return 4; // four
            case 5: return 4; // five
            case 6: return 3; // six
            case 7: return 5; // seven
            case 8: return 5; // eight
            case 9: return 4; // four
        }
    if ((number >= 10) && (number <= 19))
        switch(number)
        {
            case 10: return 3; // ten
            case 11: return 6; // eleven
            case 12: return 6; // twelve
            case 13: return 8; // thirteen
            case 14: return 8; // fourteen
            case 15: return 7; // fifteen
            case 16: return 7; // sixteen
            case 17: return 9; // seventeen
            case 18: return 8; // eighteen
            case 19: return 8; // nineteen
        }
    if ((number >= 20) && (number <= 99))
        switch ((number % 100) / 10)
        {
            case 2: return 6 + letterCount(number % 10); // twenty-
            case 3: return 6 + letterCount(number % 10); // thirty-
            case 4: return 5 + letterCount(number % 10); // forty-
            case 5: return 5 + letterCount(number % 10); // fifty-
            case 6: return 5 + letterCount(number % 10); // sixty-
            case 7: return 7 + letterCount(number % 10); // seventy-
            case 8: return 6 + letterCount(number % 10); // eighty-
            case 9: return 6 + letterCount(number % 10); // ninety-
        }
    if ((number >= 100) && (number <= 999))
    {
        int value = 7; // hundred
        value += letterCount((number % 1000) / 100); // one hundred
        if ((number % 100) != 0)
            value += 3 + letterCount(number % 100); // one hundred and thirty seven
        return value;
    }
    if (number == 1000)
        return 3 + 8; // one thousand
    printf("FAIL with number %d\n", number);
    exit(1);
}

#define DOTEST(a, b) if (letterCount(a) == strlen(b)) printf("Pass %d\n", a); else printf("Fail %d\n", a); 
void test() 
{
    DOTEST(1, "one");
    DOTEST(10, "ten");
    DOTEST(15, "fifteen");
    DOTEST(50, "fifty");
    DOTEST(54, "fiftyfour");
    DOTEST(100, "onehundred");
    DOTEST(101, "onehundredandone");
    DOTEST(118, "onehundredandeighteen");
}

int main(int argc, char **argv)
{
    unsigned int value;
    unsigned int sum = 0;
    test();
    for (int i = 1; i <= 1000; i++)
    {
        value = letterCount(i);
        sum += value;
        printf("%d -> %d\n", i, value);
    }
    printf("%d\n", sum);
}
