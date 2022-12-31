#include <stdio.h>
#define EmptyFile      -1
#define IncorrectInput -2

int sign(int numb)
{
    if (numb < 0)
        return -1;
    else if (numb == 0)
        return 0;
    else
        return 1;
}

int calculate(FILE*f, int*counter)
{
    int numb, prevSign, counterOfChanges = 0;

    if ((fscanf(f, "%i", &numb)) != 1)
        return Empty_file;

    prevSign = sign(numb);
    *counter += 1;
    while (fscanf(f, "%i", &numb) == 1)
    {
        if ((numb * prevSign <= 0) && !(prevSign >= 0 && numb >= 0))
            counterOfChanges += 1;

        *counter += 1;
        prevSign = sign(numb);
    }

    return counterOfChanges;
}

int main()
{
    int resource, counter = 0;

    resource = calculate(stdin, &counter);
    if (resource == Empty_file)
    {
        fprintf(stdout, "The sequence is empty!\n");
        return EmptyFile;
    }
    if (counter != 1)
    {
        printf("Current sequnce changes its sign %i times\n", resource);
        return 0;
    }
    else
    {
        printf("There is the only one number in sequence!\n");
        return IncorrectInput;
    }
}
