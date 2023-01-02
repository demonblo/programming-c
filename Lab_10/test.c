#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

#define OK                        0
#define EMPTY                    -1
#define NOT_FOUND                -2
#define LENGTH_ERRORR            -3
#define INPUT_ERROR              -4

void test_check_date()
{
    int err_cnt = 0;
    {
        char date[10] = "00.00.0000", *cur_date = date;
        if (!check_date(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "01.00.0000", *cur_date = date;
        if (check_date(cur_date))
            err_cnt++;
    }
    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "SUCCESSFULLY");
}

void test_check_date_for_late()
{
    int err_cnt = 0;
    {
        char date[10] = "01.02.1993", *cur_date = date;
        if (!check_date_for_late(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "31.01.1993", *cur_date = date;
        if (!check_date_for_late(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "02.06.1882", *cur_date = date;
        if (!check_date_for_late(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "02.02.1993", *cur_date = date;
        if (check_date_for_late(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "01.01.1994", *cur_date = date;
        if (check_date_for_late(cur_date))
            err_cnt++;
    }
    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "SUCCESSFULLY");
}

void test_check_date_for_correct()
{
    int err_cnt = 0;
    {
        char date[10] = "28.02.1993", *cur_date = date;
        if (!check_date_for_correct(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "28.02.1992", *cur_date = date;
        if (check_date_for_correct(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "27.02.1993", *cur_date = date;
        if (check_date_for_correct(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "31.01.1993", *cur_date = date;
        if (check_date_for_correct(cur_date))
            err_cnt++;
    }
    {
        char date[10] = "30.04.1994", *cur_date = date;
        if (check_date_for_correct(cur_date))
            err_cnt++;
    }
    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "SUCCESSFULLY");
}

int main()
{
    test_check_date();
    test_check_date_for_late();
    test_check_date_for_correct();
    return 0;
}
