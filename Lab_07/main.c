#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 32
#define Key_error 53
#define Doesnt_exist     -1
#define Emptiness        -2
#define Incorrect_input  -3
typedef

struct
{
    char first_name[32], last_name[32];
    unsigned int marks[4];
}
students;

int sort_of_journal(students journal[], int count)
{
    students temporary;
    int position_to_swap;
    int i, j;

    for (i = 0; i < count - 1; i++)
    {
        position_to_swap = i;
        for (j = i + 1; j < count; j++)
        {
            if (strcmp(journal[position_to_swap].first_name,
                journal[j].first_name) > 0)
                position_to_swap = j;
        }
        temporary = journal[position_to_swap];
        journal[position_to_swap] = journal[i];
        journal[i] = temporary;
    }

    for (i = 0; i < count - 1; i++)
    {
        position_to_swap = i;
        for (j = i + 1; j < count; j++)
        {
            if (strcmp(journal[position_to_swap].last_name,
                journal[j].last_name) > 0)
                position_to_swap = j;
        }

        temporary = journal[position_to_swap];
        journal[position_to_swap] = journal[i];
        journal[i] = temporary;
    }

    return 0;
}

int append_to_journal(FILE*f, students journal[])
{
    char string[256];
    char first_name[11], last_name[26];
    char mark_1[8], mark_2[8], mark_3[8], mark_4[8];
    int count = 0, letter_string = 0, letter_each = 0;

    while (1)
    {
        fgets(string, 256, f);
        letter_string = 0;
        letter_each = 0;

        if (feof(f) && ((int)strlen(string) == 0))
            break;
        while (string[letter_string] != ' ')
        {
            last_name[letter_each] = string[letter_string];
            letter_string++;
            letter_each++;
            if (letter_each > 25)
                return Incorrect_input;
        }

        last_name[letter_each] = '\0';
        letter_each = 0;
        while (string[letter_string] == ' ')
            letter_string++;

        while (string[letter_string] != ' ')
        {
            first_name[letter_each] = string[letter_string];
            letter_string++;
            letter_each++;
            if (letter_each > 10)
                return Incorrect_input;
        }

        first_name[letter_each] = '\0';
        letter_each = 0;
        while (string[letter_string] == ' ')
            letter_string++;

        while (string[letter_string] != ' ')
        {
            if (('0' <= string[letter_string]) && (string[letter_string] <= '9'))
                mark_1[letter_each] = string[letter_string];
            else
                return Incorrect_input;
            letter_string++;
            letter_each++;
        }

        while (string[letter_string] == ' ')
            letter_string++;

        letter_each = 0;
        while (string[letter_string] != ' ')
        {
            if (('0' <= string[letter_string]) && (string[letter_string] <= '9'))
                mark_2[letter_each] = string[letter_string];
            else
                return Incorrect_input;

            letter_string++;
            letter_each++;
        }

        while (string[letter_string] == ' ')
            letter_string++;

        letter_each = 0;
        while (string[letter_string] != ' ')
        {
            if (('0' <= string[letter_string]) && (string[letter_string] <= '9'))
                mark_3[letter_each] = string[letter_string];
            else
                return Incorrect_input;
            letter_string++;
            letter_each++;
        }

        while (string[letter_string] == ' ')
            letter_string++;

        letter_each = 0;
        while ((string[letter_string] != '\0') && (string[letter_string] != '\n')
            && (string[letter_string] != EOF))
        {
            if (('0' <= string[letter_string]) && (string[letter_string] <= '9'))
                mark_4[letter_each] = string[letter_string];
            else
                return Incorrect_input;
            letter_string++;
            letter_each++;
        }

        strcpy(journal[count].last_name, last_name);
        strcpy(journal[count].first_name, first_name);
        journal[count].marks[0] = atoi(mark_1);
        journal[count].marks[1] = atoi(mark_2);
        journal[count].marks[2] = atoi(mark_3);
        journal[count].marks[3] = atoi(mark_4);
        count++;
        if ((string[letter_string] == EOF) || (string[letter_string] == '\0'))
            break;
        strcpy(string, "\0");
    }

    return count;
}

int main(int argc, char**argv)
{
    FILE*f;
    students journal[N];
    int count = 0;

    if ((argc == 3) && (strcmp(argv[1], "st") == 0))
    {
        f = fopen(argv[2], "r");
        if (f == NULL)
        {
            printf("Current file doens`t exit\n!");
            return Doesnt_exist;
        }
        count = append_to_journal(f, journal);
        fclose(f);
        if (count == 0)
        {
            printf("Current file is empty!\n");
            return Emptiness;
        }
        if (count == Incorrect_input)
        {
            printf("Incorrect input!\n");
            return Incorrect_input;
        }
        sort_of_journal(journal, count);
        for (int i = 0; i < count; i++)
        {
            printf("%s ", journal[i].last_name);
            printf("%s ", journal[i].first_name);
            for (int j = 0; j < 4; j++)
                printf("%u ", journal[i].marks[j]);

            printf("\n");
        }

        return 0;
    }
    else if ((argc == 5) && (strcmp(argv[1], "ft") == 0))
    {
        char substring[32];
        int flag = 1;
        int students = 0;

        f = fopen(argv[2], "r");
        if (f == NULL)
        {
            printf("File doens`t exits!");
            return Doesnt_exist;
        }
        count = append_to_journal(f, journal);
        fclose(f);
        if (count == 0)
        {
            printf("File is empty!");
            return Emptiness;
        }
        if (count == Incorrect_input)
        {
            printf("Invalid input data!");
            return Incorrect_input;
        }
        f = fopen(argv[3], "w");
        strcpy(substring, argv[4]);
        for (int i = 0; i < count; i++)
        {
            flag = 1;
            for (int j = 0; j < strlen(substring); j++)
                if (substring[j] != journal[i].last_name[j])
                    flag = 0;

            if (flag)
            {
                fprintf(f, "%s %s %u %u %u %u\n", journal[i].last_name,
                    journal[i].first_name, journal[i].marks[0],
                    journal[i].marks[1], journal[i].marks[2],
                    journal[i].marks[3]);
                students++;
            }
        }

        fclose(f);
        if (students != 0)
            return 0;
        else
        {
            printf("NO required students!\n");
            return Emptiness;
        }
    }

    return Key_error;
}




