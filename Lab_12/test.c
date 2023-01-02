#include "header.h"

void test_check_for_simpliness()
{
    int err_cnt = 0;
    {
        int numb = 10;
        if (check_for_simpliness(numb))
            err_cnt++;
    }
    {
        int numb = 4;
        if (check_for_simpliness(numb))
            err_cnt++;
    }
    {
        int numb = 27;
        if (check_for_simpliness(numb))
            err_cnt++;
    }
    {
        int numb = 2;
        if (!check_for_simpliness(numb))
            err_cnt++;
    }
    {
        int numb = 3;
        if (!check_for_simpliness(numb))
            err_cnt++;
    }
    {
        int numb = 23;
        if (!check_for_simpliness(numb))
            err_cnt++;
    }
    {
        int numb = 97;
        if (!check_for_simpliness(numb))
            err_cnt++;
    }
    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "SUCCESSFULLY");
}

void test_power_of_simpliness()
{
    int err_cnt = 0;
    {
        int numb = 10, i = 2;
        if (power_of_simpliness(numb, i) != 1)
            err_cnt++;
    }
    {
        int numb = 27, i = 3;
        if (power_of_simpliness(numb, i) != 3)
            err_cnt++;
    }
    {
        int numb = 27, i = 2;
        if (power_of_simpliness(numb, i) != 0)
            err_cnt++;
    }
    {
        int numb = 23, i = 23;
        if (power_of_simpliness(numb, i) != 1)
            err_cnt++;
    }
    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "SUCCESSFULLY");
}

int main()
{
    test_check_for_simpliness();
    test_power_of_simpliness();

    return 0;
}
