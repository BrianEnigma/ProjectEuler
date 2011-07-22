#include <stdio.h>
#include <string.h>
#include <stdlib.h>
unsigned char valueToNumber[] = {'?','?','2','3','4','5','6','7','8','9','T','J','Q','K','A'};
unsigned char valueToSuit[] = {'H','D','S','C'};
#define JACK    11
#define QUEEN   12
#define KING    13
#define ACE     14
typedef struct {
    unsigned char number; // 2..14
    unsigned char suit;   // 0..4
} Card;
typedef enum {
    HighCard = 0,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    Straight,
    Flush,
    FullHouse,
    FourOfAKind,
    StraightFlush,
    RoyalFlush
} WinType;
const char *valueToWinType[] = {"HighCard","OnePair","TwoPair","ThreeOfAKind","Straight","Flush","FullHouse","FourOfAKind","StraightFlush","RoyalFlush"};

void printCard(Card *card)
{
    printf("%c%c ", valueToNumber[card->number], valueToSuit[card->suit]);
}

void printHand(const char *prefix, Card *card, const char *suffix)
{
    printf("%s", prefix);
    for (int i = 0; i < 5; i++)
        printCard(card + i);
    printf("%s", suffix);
}

void checkWinType(Card *card, WinType *winType, unsigned int *highestInWin, unsigned int *secondHighestInWin)
{
    unsigned char isStraight = 1;
    unsigned char isFlush = 0;
    unsigned char pairCount = 0;
    unsigned char hasThreeOfAKind = 0;
    char suitCount[4] = {0,0,0,0};
    char numberCount[15];
    memset(numberCount, 0, sizeof(numberCount));
    *highestInWin = 0;
    *secondHighestInWin = 0; // the other pair of two pair
    // check for flush
    for (int i = 0; i < 5; i++)
    {
        suitCount[(*(card + i)).suit]++;
        numberCount[(*(card + i)).number]++;
    }
    for (int i = 0; i < 4; i++)
        if (suitCount[i] == 5)
            isFlush = 1;
    // Check for straight
    for (int i = 0; i < 4; i++)
        if ((*(card + i)).number != (*(card + i + 1)).number - 1)
            isStraight = 0;
    if (isStraight && isFlush)
    {
        // royal flush
        if ((*(card + 4)).number == ACE)
        {
            *winType = RoyalFlush;
            *highestInWin = (*(card + 4)).number;
            return;
        }
        // straight flush
        *winType = StraightFlush;
        *highestInWin = (*(card + 4)).number;
        return;
    }
    // four of a kind
    for (int number = ACE; number >= 2; number--)
        if (numberCount[number] == 4)
        {
            *winType = FourOfAKind;
            *highestInWin = number;
            return;
        } else if (numberCount[number] == 3) {
            hasThreeOfAKind = 1;
        }
    // count pairs
    for (int number = ACE; number >= 2; number--)
        if (numberCount[number] == 2) {
            pairCount++;
            if (!*highestInWin)
                *highestInWin = number;
        }
    // full house
    if (pairCount && hasThreeOfAKind)
    {
        *winType = FullHouse;
        *highestInWin = 0;
        for (int number = ACE; (number >= 2) && (*highestInWin == 0); number--)
            if (numberCount[number] == 3)
                *highestInWin = number;
        return;
    }
    // flush
    if (isFlush)
    {
        *winType = Flush;
        *highestInWin = 0; //(*(card + 4)).number;
        return;
    }
    // straight
    if (isStraight)
    {
        *winType = Straight;
        *highestInWin = (*(card + 4)).number;
        return;
    }
    // three of a kind
    if (hasThreeOfAKind) {
        *winType = ThreeOfAKind;
        *highestInWin = 0;
        for (int number = ACE; (number >= 2) && (*highestInWin == 0); number--)
            if (numberCount[number] == 3)
                *highestInWin = number;
        return;
    }
    // Two pair, one pair
    if (pairCount)
    {
        *highestInWin = *secondHighestInWin = 0;
        for (int number = ACE; (number >= 2) && (*highestInWin == 0) && (*secondHighestInWin == 0); number--)
            if (numberCount[number] == 2)
            {
                if (!*highestInWin)
                    *highestInWin = number;
                else if (!*secondHighestInWin)
                    *secondHighestInWin = number;
            }
        *winType = (pairCount == 2) ? TwoPair : OnePair;
        return;
    }
    *winType = HighCard;
    *highestInWin = (*(card + 4)).number;
}

int determineWinner(Card *player1, Card *player2)
{
    WinType player1Win, player2Win;
    unsigned int highestInWinPlayer1, highestInWinPlayer2;
    unsigned int secondHighestInWinPlayer1, secondHighestInWinPlayer2;
    unsigned char player1Numbers[14], player2Numbers[14];
    checkWinType(player1, &player1Win, &highestInWinPlayer1, &secondHighestInWinPlayer1);
    checkWinType(player2, &player2Win, &highestInWinPlayer2, &secondHighestInWinPlayer2);
    printf("Player1:%s high %c | Player2:%s high %c\n",
            valueToWinType[player1Win], valueToNumber[highestInWinPlayer1],
            valueToWinType[player2Win], valueToNumber[highestInWinPlayer2]);
    // Check for a clear win
    if (player1Win > player2Win)
        return 1;
    else if (player2Win > player1Win)
        return 2;
    // ASSERT: if we hit here, there's a tie of some kind (e.g. one has a pair of queens and the other has a pair of 2s)
    if (highestInWinPlayer1 > highestInWinPlayer2)
        return 1;
    else if (highestInWinPlayer2 > highestInWinPlayer1)
        return 2;
    if (secondHighestInWinPlayer1 > secondHighestInWinPlayer2)
        return 1;
    else if (secondHighestInWinPlayer2 > secondHighestInWinPlayer1)
        return 2;
    // ASSERT: we're in a true tie (i.e. each has a pair of queens)
    memset(player1Numbers, 0, sizeof(player1Numbers));
    memset(player2Numbers, 0, sizeof(player2Numbers));
    for (int i = 0; i < 5; i++)
    {
        player1Numbers[(*(player1 + i)).number]++;
        player2Numbers[(*(player2 + i)).number]++;
    }
    for (int number = ACE; number >= 2; number--)
        if (player1Numbers[number] > player2Numbers[number])
            return 1;
        else if (player2Numbers[number] > player1Numbers[number])
            return 2;
    printf("WTF?\n");
    printHand("Player1: ", player1, "\n");
    printHand("Player2: ", player2, "\n");
    exit(1);
}

void parseCard(Card *card, const char *s)
{
    if ((*s >= '2') && (*s <= '9'))
        card->number = *s - '0';
    else if (*s == 'T')
        card->number = 10;
    else if (*s == 'J')
        card->number = JACK;
    else if (*s == 'Q')
        card->number = QUEEN;
    else if (*s == 'K')
        card->number = KING;
    else if (*s == 'A')
        card->number = ACE;
    switch(*(s + 1))
    {
        case 'H': card->suit = 0; break;
        case 'D': card->suit = 1; break;
        case 'S': card->suit = 2; break;
        case 'C': card->suit = 3; break;
    }
}

void testSwap(Card *card1, Card *card2)
{
    Card temp;
    // Card 2 is higher, swap / or cards are the same, but suits are not in order
    if (    (card2->number < card1->number)
         || ((card2->number == card1->number) && (card2->suit < card1->suit))
       )
    {
        memcpy(&temp, card1, sizeof(Card));
        memcpy(card1, card2, sizeof(Card));
        memcpy(card2, &temp, sizeof(Card));
    }
}

void parseHand(Card *hand, const char *s)
{
    // Parse it
    for (int i = 0; i < 5; i++)
        parseCard(hand + i, s + 3 * i);
    // Sort it low..high by suit
    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++)
            testSwap(hand + i, hand + j);
}

void test()
{
    Card player1[5], player2[5];
    memset(player1, 0, sizeof(player1)); memset(player2, 0, sizeof(player2));
    // Givens:
    parseHand(player1, "5H 5C 6S 7S KD"); parseHand(player2, "2C 3S 8S 8D TD");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    parseHand(player1, "5D 8C 9S JS AC"); parseHand(player2, "2C 5C 7D 8S QH");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    parseHand(player1, "2D 9C AS AH AC"); parseHand(player2, "3D 6D 7D TD QD");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    parseHand(player1, "4D 6S 9H QH QC"); parseHand(player2, "3D 6D 7H QD QS");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    parseHand(player1, "2H 2D 4C 4D 4S"); parseHand(player2, "3C 3D 3S 9S 9D");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    // My testing:
    parseHand(player1, "TH JH QH KH AH"); parseHand(player2, "3C 3D 3S 9S 9D");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    parseHand(player1, "TH JH QH KH AC"); parseHand(player2, "3C 3D 3S 9S 9D");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    parseHand(player1, "2H 3H 4H 5H 6H"); parseHand(player2, "3C 3D 3S 9S 9D");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    parseHand(player1, "2H 2C 2D 2S 6H"); parseHand(player2, "3C 3D 3S 9S 9D");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
    parseHand(player1, "2H 2C 6D 6S 7H"); parseHand(player2, "3C 3D 3S 9S 9D");
    printHand("player1:", player1, " "); printHand("player2:", player2, "\n");
    printf("Player%d wins\n", determineWinner(player1, player2));
}

int main(int argc, char **argv)
{
    FILE *f;
    char line[80];
    unsigned int wins[3];
    int throttle = 20;
#if 0
    test();
    return 0;
#endif
    f = fopen("poker.txt", "r");
    if (!f)
        return 1;
    memset(wins, 0, sizeof(wins));
    while ((fgets(line, sizeof(line), f)) != NULL)
    {
        int winner;
        Card player1[5], player2[5];
        line[sizeof(line) - 1] = 0;
        parseHand(player1, &line[0]);
        parseHand(player2, &line[15]);
        winner = determineWinner(player1, player2);
        wins[winner]++;
        printf("%78d\n", winner);
        if (throttle > 0)
        {
            throttle--;
            printHand("player1:", player1, " ");
            printHand("player2:", player2, " ");
            printf("Winner is Player%d\n\n", winner);
        }
#if 0
        if (throttle == 0)
            break;
#endif
    }
    printf("Total wins: player1=%d player2=%d\n", wins[1], wins[2]);
    return 0;
}
