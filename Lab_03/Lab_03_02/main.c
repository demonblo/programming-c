# include <stdio.h>
# include <math.h>

# define FileError          -1
# define EmptyFile          -2
# define IncorrectInput     -3
//Правило 3 сигм
int countNumbers(FILE *f)
{
    int counter = 0, scan = 0;
    float numb;

    scan = fscanf(f, "%f", &numb);
    while (scan == 1)
    {
        counter++;
        scan = fscanf(f, "%f", &numb);
    }

    if (scan == EOF)
        return counter;
    else
        return IncorrectInput;
}

float medium(FILE *f, int count)
{
    float numb, sum = 0;

    while (fscanf(f, "%f", &numb) != EOF)
        sum += numb;

    return sum / count;
}

float sigma(FILE *f, int count, float medium)
{
    float temp, sumXSum = 0;

    while (fscanf(f, "%f", &temp) != EOF)
        sumXSum += (temp - medium) * (temp - medium);

    return sqrt(sumXSum / count);
}

int threeSigmasRule(FILE *f, float fMedium, float fSigma)
{
    float numb;

    while (fscanf(f, "%f", &numb) != EOF)
        if ((numb - fMedium >= 3 * fSigma) || (fMedium - numb >= 3 * fSigma))
            return 0;
    return 1;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Incorrect console input!\n");
        return FileError;
    }
    FILE* file = fopen(argv[1], "rt");
    int counter;
    float fMedium, fSigma;

    if (!file)
    {
        printf("Incorrect file!\n");
        return FileError;
    }
    counter = countNumbers(file);
    if (counter > 0)
        rewind(file);
    else if (!counter)
    {
        printf("File is empty!\n");
        fclose(file);
        return EmptyFile;
    }
    else
    {
        printf("Incorrect input data!");
        fclose(file);
        return IncorrectInput;
    }
    fMedium = medium(file, counter);
    rewind(file);
    fSigma = sigma(file, counter, fMedium);
    rewind(file);
    if (threeSigmasRule(file, fMedium, fSigma))
        printf("The rule of three sigmas has worked!\n");
    else
        printf("The rule of three sigmas hasn't worked!\n");
    fclose(file);
    return 0;
}
