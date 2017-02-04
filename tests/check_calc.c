#include <stdlib.h>
#include <stdio.h>
#include <check.h>
#include "../src/calc.h"

typedef struct _TestVectorStruct
{
    char *arg1;
    char *arg2;
    int opcode;
    char *rez;
} TestVectorStruct;

TestVectorStruct test[10];
int idx = 0;

Variable *v;

int StrCmp(char *arg1, char *arg2)
{
    for(int i = 0;arg1[i] != '\0';i++)
    {
        if(arg1[i] != arg2[i])
        {
            printf("\n%d\n",i);
            return 0;
        }
    }
    return 1;
}

START_TEST(test_var_create)
{
    v = var_create(test[idx].arg1,test[idx].arg2);
    printf("Sample Input - %d",idx+1);
    printf(", Arg1 = %s",test[idx].arg1);
    printf(", Arg2 = %s",test[idx].arg2);
    printf(", Operation = %d",test[idx].opcode);
    printf(", Expected Result = %s",test[idx].rez);
    printf("\n");
    if(v == NULL)
    {
        printf("Test 1 - Failed - Either of the Two Arguments is Invalid\n");
    }
    else
    {
        printf("Test 1 - Passed\n");
        char *rez = operation(v, test[idx].opcode);
        if (rez == NULL)
        {
            printf("Test 2 - Failed - Subtraction Not Possible! - Failed\n");
        }
        else if(StrCmp(rez,test[idx].rez) == 0)
        {
            printf("Test 2 - Failed - Result Not Correct\n");
            printf("Exp Result = %s, Actual Result = %s\n",test[idx].rez,rez);
        }
        else if(StrCmp(rez,test[idx].rez) == 1)
        {
            printf("Test 2 - Passed\n");
        }
    }
    var_free(v);
}
END_TEST

Suite *money_suite(void)
{
    Suite *s;
    s = suite_create("Calculator");
    TCase *tc_core;
    TCase *tc_limits;
    
    /* Core Test Cases */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_var_create);
    suite_add_tcase(s, tc_core);

    /*  Limits Test Case  */
//    tc_limits = tcase_create("Operation");
//    tcase_add_test(tc_limits, test_var_operation);
//    suite_add_tcase(s, tc_limits);
    
    return s;
}


int main(int argc, char *argv[])
{
    test[0].arg1 = "XIV"; test[0].arg2 = "LX"; test[0].opcode = 1; test[0].rez = "LXXIV\0";
    test[1].arg1 = "II"; test[1].arg2 = "II"; test[1].opcode = 1;  test[1].rez = "IV";
    test[2].arg1 = "CXXII"; test[2].arg2 = "LXI"; test[2].opcode = 1;  test[2].rez = "CLXXXIII";
    test[3].arg1 = "LXVIII"; test[3].arg2 = "XII"; test[3].opcode = 2;  test[3].rez = "LVI";
    test[4].arg1 = "CXXIX"; test[4].arg2 = "XLIII"; test[4].opcode = 2;  test[4].rez = "LXXXVI";
    test[5].arg1 = "X"; test[5].arg2 = "I"; test[5].opcode = 2;  test[5].rez = "IX";
    test[6].arg1 = "XLIII"; test[6].arg2 = "CXXIX"; test[6].opcode = 2;  test[6].rez = '\0';
    test[7].arg1 = "CCCLXVIIII"; test[7].arg2 = "DCCCXXXXV"; test[7].opcode = 1;  test[7].rez = "MCCXIV";
    test[8].arg1 = "D"; test[8].arg2 = "C"; test[8].opcode = 1;  test[8].rez = "DC";
    test[9].arg1 = "XC"; test[9].arg2 = "LB"; test[9].opcode = 2;  test[9].rez = '\0';

    int number_failed;
    Suite *s;
    SRunner *sr;
    s = money_suite();
    sr = srunner_create(s);

    printf("--------------------\n");
    printf("***STARTING TESTS***\n");

    for(int i = 0;i<10;i++)
    {
        srunner_run_all(sr, CK_NORMAL);
        number_failed = srunner_ntests_failed(sr);
        idx++;
        printf("\n");
        printf("\n");
    }
    srunner_free(sr);

    printf("***ENDING TESTS***\n");
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
