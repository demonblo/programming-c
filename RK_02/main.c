#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define Max_length 100
#define Delimetr " "

void output(int i, char *words[])
{
    int size = i;

    i = 0;
    for (; i < size; i++)
    {
        int is_unique = 0;
        for (int j = 0; j < size && is_unique == 0; j++)
        {
            if (i == j)
                continue;
            int string_compare = strcmp(words[i], words[j]);
            if (string_compare == 0)
                is_unique = 1;
        }

        if (is_unique == 0)
            printf("%s ", words[i]);
    }

    printf("\n");
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Incorrect console input!\n");
        return -1;
    }
    FILE* fp = fopen(argv[1], "rt");
    char buf[Max_length];

    printf("Answer:\n");
    while(fgets(buf, sizeof(buf), fp) != NULL)
    {
        char *ptr = strtok(buf, Delimetr);
        char *words[Max_length];
        int i = 0;

        while(ptr != NULL)
        {
            char *pos;
            if ((pos = strchr(ptr, '\n')) != NULL)
                *pos = '\0';
            words[i++] = ptr;
            ptr = strtok(NULL, Delimetr);
        }

        output(i, words);
    }

    fclose(fp);
}

