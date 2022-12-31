#include<stdio.h>
#include<string.h>

#define Legth_string        256
#define Quantity_of_words    16
#define Word_length          17
#define Empty_error          -1
#define Length_error         -2
#define Words_error          -3
#define String_length_error  -4

int uniqueWords(char matrixOfWords[Quantity_of_words][32], int initialCount)
{
    int i, j;

    for (i = 0; i < initialCount; i++)
    {
        for (j = i + 1; j < initialCount; j++)
            if (strcmp(matrixOfWords[j], matrixOfWords[i]) == 0)
            {
                strcpy(matrixOfWords[j], matrixOfWords[initialCount - 1]);
                initialCount--;
                j--;
            }
    }

    return initial_count;
}

int splitOnWords(char matrixOfWords[Quantity_of_words][32], int initialCount)
{
    char c = getchar();
    char word[32];
    int lengthOfWord = 0, countSymbol = 0;

    if ((c == '\n') || (c == '\0'))
        return Empty_error;
    while ((c == ' ') || (c == ',') || (c == ';') || (c == ':') ||
        (c == '-') || (c == '.') || (c == '!') || (c == '?'))
    {
        countSymbol++;
        c = getchar();
    }

    while ((c != '\n') && (c != '\0') && (c != EOF))
    {
        if ((c == ' ') || (c == ',') || (c == ';') || (c == ':') ||
            (c == '-') || (c == '.') || (c == '!') || (c == '?'))
        {
            if (lengthOfWord != 0)
            {
                if ((initialCount + 1) > QuantityOfWords)
                    return Words_error;
                word[lengthOfWord] = '\0';
                strcpy(matrixOfWords[initialCount], word);
                initialCount++;
                lengthOfWord = 0;
            }
        }
        else
        {
            // Checking space for '/0'
            if (lengthOfWord == Word_length - 1)
                return Length_error;
            word[lengthOfWord] = c;
            lengthOfWord++;
        }
        countSymbol++;
        c = getchar();
    }

    if (lengthOfWord != 0)
    {
        if ((initialCount + 1) > Quantity_of_words)
            return Words_error;
        if (lengthOfWord > Word_length - 1)
            return Length_error;
        word[lengthOfWord] = '\0';
        strcpy(matrixOfWords[initialCount], word);
        initialCount++;
        lengthOfWord = 0;
    }
    if (countSymbol > Legth_string)
        return String_length_error;
    return initialCount;
}

void sortWords(char matrixOfWords[Quantity_of_words][32], int initialCnt)
{
    int posToSwap;
    char tmp[32];

    for (int i = 0; i < initialCnt; i++)
    {
        posToSwap = i;
        for (int j = i; j < initialCnt; j++)
            if (strcmp(matrixOfWords[j], matrixOfWords[posToSwap]) < 0)
                posToSwap = j;

        strcpy(tmp, matrixOfWords[posToSwap]);
        strcpy(matrixOfWords[posToSwap], matrixOfWords[i]);
        strcpy(matrixOfWords[i], tmp);
    }
}

typedef char matrWordsT[Quantity_of_words][32];

int main()
{
    matrWordsT matrixOfWords;
    int initialCount = 0;

    initialCount = splitOnWords(matrixOfWords, initialCount);
    if (initialCount <= 0)
    {
        if (initialCount == Length_error)
        {
            printf("Incorrect length!\n");
            return Length_error;
        }
        if (initialCount == Words_error)
        {
            printf("Incorrect words!\n");
            return Words_error;
        }
        if (initialCount == String_length_error)
        {
            printf("Incorrect length of string!\n");
            return String_length_error;
        }
        if ((initialCount == Empty_error) || (!initialCount))
        {
            printf("Error!\n");
            return Empty_error;
        }
    }
    initialCount = uniqueWords(matrixOfWords, initialCount);
    sortWords(matrixOfWords, initialCount);
    printf("Result:");
    for (int i = 0; i < initialCount; i++)
        printf("%s ", matrixOfWords[i]);

    return 0;
}
