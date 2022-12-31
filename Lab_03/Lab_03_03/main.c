#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define Error_of_seek        -1
#define Error_of_read        -2
#define Error_of_write       -3
#define Error_console        -4
#define Error_mode           -5
#define Scan_error           -6
#define Empty_file           -7
#define File_size            10

int getNumberByPos(int *prt, FILE *file, long int position)
{
    int scan;

    scan = fseek(file, sizeof(int) * position, SEEK_SET);
    if (scan)
        return Error_of_seek;
    scan = fread(prt, sizeof(int), 1, file);
    if (scan)
        return 0;
    else
        return Error_of_read;
}

int putNumberByPos(int *prt, FILE *file, long int position)
{
    int scan;

    scan = fseek(file, sizeof(int) * position, SEEK_SET);
    if (scan)
        return Error_of_seek;
    scan = fwrite(prt, sizeof(int), 1, file);
    if (scan)
        return 0;
    else
        return Error_of_write;
}

int swap(FILE *file, long int i, long int j)
{
    int temporary_i;
    int temporary_j;
    getNumberByPos(&temporary_i, file, i);
    getNumberByPos(&temporary_j, file, j);
    putNumberByPos(&temporary_i, file, j);
    putNumberByPos(&temporary_j, file, i);
    return 0;
}

int creationOfFile(char *nameOfFile)
{
    FILE* file = fopen(nameOfFile, "wb");
    int n, temporary;

    setbuf(stdout, NULL);
    if (!file)
        return Scan_error;
    n = 1 + rand() % (File_size - 1);
    for (long int position = 0; position < n; position++)
    {
        temporary = -1000 + rand() % 2000;
        printf("%d ", temporary);
        putNumberByPos(&temporary, file, position);
    }

    fclose(file);
    return 0;
}

int printOfFile(char *nameOfFile)
{
    FILE* file = fopen(nameOfFile, "rb");
    long int pos = 0;
    int temporary, scan;

    setbuf(stdout, NULL);
    if (!file)
        return Scan_error;

    scan = getNumberByPos(&temporary, file, pos);
    if (scan)
    {
        fclose(file);
        return Empty_file;
    }
    while (!scan)
    {
        printf("%d ", temporary);
        pos++;
        scan = getNumberByPos(&temporary, file, pos);
    }

    fclose(file);
    return 0;
}

int sortOfFile(char *nameOfFile)
{
    FILE* file = fopen(nameOfFile, "rb+wb");
    long int n = 0, i, j, minPosition;
    int temporary, iteration, min;

    setbuf(stdout, NULL);
    if (!file)
        return Scan_error;
    while (!getNumberByPos(&temporary, file, n))
        n++;

    if (!n)
    {
        fclose(file);
        return Empty_file;
    }
    for (i = 0; i < n - 1; i++)
    {
        getNumberByPos(&min, file, i);
        minPosition = i;
        for (j = i + 1; j < n; j++)
        {
            getNumberByPos(&iteration, file, j);
            if (iteration < min)
            {
                min = iteration;
                minPosition = j;
            }
        }
        if (minPosition != i)
            swap(file, i, minPosition);
    }

    fclose(file);
    return 0;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int answer = Error_mode;
    if (argc == 3)
    {
        if (!strcmp(argv[1], "c"))
            answer = creationOfFile(argv[2]);
        if (!strcmp(argv[1], "p"))
            answer = printOfFile(argv[2]);
        if (!strcmp(argv[1], "s"))
            answer = sortOfFile(argv[2]);
    }
    else
        answer = Error_console;

    switch (answer)
    {
        case Empty_file:
            printf("Current file is empty!\n");
            break;
        case Error_console:
            printf("Incorrect arguments format in colsole!\n");
            break;
        case Scan_error:
            printf("File scan failed!\n");
            break;
        case Error_mode:
            printf("Wrong mode!\n");
            break;
    }

    return answer;
}
