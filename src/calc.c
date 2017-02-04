#include <stdlib.h>
#include "calc.h"
#define min(a,b) (a<=b?a:b)

// Structure to hold Roman Literals
struct Variable {
    char *arg1;
    char *arg2;
};

// Like a Constructor
Variable *var_create(char *arg1, char *arg2) {
    Variable *v;
    if((CheckValidArg(arg1) == 0) || (CheckValidArg(arg2) == 0)) {
        return NULL;
    }
    v = (Variable *)malloc(sizeof(Variable));
    v->arg1 = arg1;
    v->arg2 = arg2;

    return v;
}

// This func takes in a var struct and the opcode depending on operation (1-Addition 2-Subtraction)
// and returns the char array
char *operation(Variable *v, int opcode) {
    if(opcode == 1) {
        return result_add(v);
    }
    else if(opcode == 2) {
        return result_subtract(v);
    }
}

// This func perform add operation
char *result_add(Variable *v) {
    char *arg1 = Extend(v->arg1);
    char *arg2 = Extend(v->arg2);
    char *Concatenate = (char *)malloc(sizeof(char));
    int len = 0;
    for(int i = 0;arg1[i] != '\0';i++)
    {
        Concatenate[len] = arg1[i]; len++;
    }
    for(int i = 0;arg2[i] != '\0';i++)
    {
        Concatenate[len] = arg2[i]; len++;
    }
    Concatenate[len] = '\0';
    char *Result = Group(Concatenate);
    /*for(int i = 0;Result[i] != '\0';i++)
    {
        printf("%c,",Result[i]);
    }
    printf("\n");*/
    return Result;
}

// This func perform sub operation
char *result_subtract(Variable *v)
{
    if(ConvertRomanToInt(v->arg1) <= ConvertRomanToInt(v->arg2))
    {
        return NULL;
    }
    char *arg1 = Extend(v->arg1);
    char *arg2 = Extend(v->arg2);
    int *numArg1 = (int *)malloc(7*sizeof(int));
    numArg1 = Enum(arg1);
    int *numArg2 = (int *)malloc(7*sizeof(int));
    numArg2 = Enum(arg2);

    char *OrderRez = CrossOutSymbolsSub(numArg1, numArg2);
    char *Result = Group(OrderRez);

    /*for(int i = 0;Result[i] != '\0';i++)
    {
        printf("%c,",Result[i]);
    }
    printf("\n");*/
    return Result;
}

//This function is used to cross out common symbols during subtraction.
//For example if the Var1 = LXVIII & Var2 = XII
//So the common symbols are XII, Function cross these symbols out
//Also it returns 1 char array
//In the above example the characters in Var2 easily cancels with some of those in Var1
//Now take another example
//Var1 = CXXIX, Var2 = XLIII
//Var1 = CVI, Var2 = XX
//Var1 = LXXXXXVII, Var2 = XX
//As we can see we needed 2 X's so we converted C->L->X to elimiate second char array
char *CrossOutSymbolsSub(int *numArg1, int *numArg2)
{
    for(int i = 0;i<7;i++)
    {
        if (min(numArg1[i],numArg2[i]) != 0)
        {
            if(numArg1[i] <= numArg2[i])
            {
                numArg2[i] = numArg2[i] - numArg1[i];
                numArg1[i] = 0;
            }
            else if(numArg1[i] > numArg2[i])
            {
                numArg1[i] = numArg1[i] - numArg2[i];
                numArg2[i] = 0;
            }
        }
    }
    if(numArg2[0] == 0 && numArg2[1] == 0 && numArg2[2] == 0 && numArg2[3] == 0 && numArg2[4] == 0 && numArg2[5] == 0 && numArg2[6] == 0)
    {
        int len = 0;
        char *OrderRez = (char *)malloc(sizeof(char));
        char *x = "IVXLCDM";
        for(int i = 6;i>=0;i--)
        {
            for(int j = 0;j<numArg1[i];j++)
            {
                OrderRez[len] = x[i];
                len++;
            }
        }
        OrderRez[len] = '\0';
        /*printf("%d\n",len);
        for(int i = 0;i<len;i++)
        {
            printf("%c,",OrderRez[i]);
        }*/
        return OrderRez;
    }
    else
    {
        if(numArg2[0] != 0)
        {
            if(numArg1[0] == 0)
            {
                if(numArg1[1] != 0) { numArg1[1]--; numArg1[0] = numArg1[0] + 5; }
                else if(numArg1[2] != 0) { numArg1[2]--; numArg1[1]++; numArg1[0] = numArg1[0] + 5; }
                else if(numArg1[3] != 0) { numArg1[3]--; numArg1[2] = numArg1[2] + 4; numArg1[1]++; numArg1[0] = numArg1[0] + 5; }
                else if(numArg1[4] != 0) { numArg1[4]--; numArg1[3]++; numArg1[2] = numArg1[2] + 4; numArg1[1]++; numArg1[0] = numArg1[0] + 5; }
                else if(numArg1[5] != 0) { numArg1[5]--; numArg1[4] = numArg1[4] + 4; numArg1[3]++; numArg1[2] = numArg1[2] + 4; numArg1[1]++; numArg1[0] = numArg1[0] + 5; }
                else if(numArg1[6] != 0) { numArg1[6]--; numArg1[5]++; numArg1[4] = numArg1[4] + 4; numArg1[3]++; numArg1[2] = numArg1[2] + 4; numArg1[1]++; numArg1[0] = numArg1[0] + 5; }
            }
        }
        if(numArg2[1] != 0)
        {
            if(numArg1[1] == 0)
            {
                if(numArg1[2] != 0) { numArg1[2]--; numArg1[1] = numArg1[1] + 2; }
                else if(numArg1[3] != 0) { numArg1[3]--; numArg1[2] = numArg1[2] + 4; numArg1[1] = numArg1[1] + 2; }
                else if(numArg1[4] != 0) { numArg1[4]--; numArg1[3]++; numArg1[2] = numArg1[2] + 4; numArg1[1] = numArg1[1] + 2; }
                else if(numArg1[5] != 0) { numArg1[5]--; numArg1[4] = numArg1[4] + 4; numArg1[3]++; numArg1[2] = numArg1[2] + 4; numArg1[1] = numArg1[1] + 2; }
                else if(numArg1[6] != 0) { numArg1[6]--; numArg1[5]++; numArg1[4] = numArg1[4] + 4; numArg1[3]++; numArg1[2] = numArg1[2] + 4; numArg1[1] = numArg1[1] + 2; }
            }
        }
        if(numArg2[2] != 0)
        {
            if(numArg1[2] == 0)
            {
                if(numArg1[3] != 0) { numArg1[3]--; numArg1[2] = numArg1[2] + 5; }
                else if(numArg1[4] != 0) { numArg1[4]--; numArg1[3]++; numArg1[2] = numArg1[2] + 5; }
                else if(numArg1[5] != 0) { numArg1[5]--; numArg1[4] = numArg1[4] + 4; numArg1[3]++; numArg1[2] = numArg1[2] + 5; }
                else if(numArg1[6] != 0) { numArg1[6]--; numArg1[5]++; numArg1[4] = numArg1[4] + 4; numArg1[3]++; numArg1[2] = numArg1[2] + 5; }
            }
        }
        if(numArg2[3] != 0)
        {
            if(numArg1[3] == 0)
            {
                if(numArg1[4] != 0) { numArg1[4]--; numArg1[3] = numArg1[3] + 2; }
                else if(numArg1[5] != 0) { numArg1[5]--; numArg1[4] = numArg1[4] + 4; numArg1[3] = numArg1[3] + 2; }
                else if(numArg1[6] != 0) { numArg1[6]--; numArg1[5]++; numArg1[4] = numArg1[4] + 4; numArg1[3] = numArg1[3] + 2; }
            }
        }
        if(numArg2[4] != 0)
        {
            if(numArg1[4] == 0)
            {
                if(numArg1[5] != 0) { numArg1[5]--; numArg1[4] = numArg1[4] + 5; }
                else if(numArg1[6] != 0) { numArg1[6]--; numArg1[5]++; numArg1[4] = numArg1[4] + 5; }
            }
        }
        if(numArg2[5] != 0)
        {
            if(numArg1[5] == 0)
            {
                if(numArg1[6] != 0) { numArg1[6]--; numArg1[5] = numArg1[5] + 2; }
            }
        }
        char *OrderRez = CrossOutSymbolsSub(numArg1,numArg2);
        return OrderRez;
    }
}

// This func checks whether the arguments are valid
// The arguments won't be valid if they contain other symbols than those included in roman literals
int CheckValidArg(char *arg)
{
    for(int i = 0;arg[i] != '\0';i++)
    {
        if(arg[i] == 'I' || arg[i] == 'V' || arg[i] == 'X' || arg[i] == 'L' || arg[i] == 'C' || arg[i] == 'D' || arg[i] == 'M')
        {
//            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

// This function enumerates each of the characters in a char array and returns an int array of length 7
int *Enum(char *arg)
{
    int *num = (int *)malloc(7*sizeof(int));
    num[0] = 0; num[1] = 0; num[2] = 0; num[3] = 0; num[4] = 0; num[5] = 0; num[6] = 0;
    for (int i = 0;arg[i] != '\0';i++)
    {
        if(arg[i] == 'I') num[0]++;
        else if(arg[i] == 'V') num[1]++;
        else if(arg[i] == 'X') num[2]++;
        else if(arg[i] == 'L') num[3]++;
        else if(arg[i] == 'C') num[4]++;
        else if(arg[i] == 'D') num[5]++;
        else if(arg[i] == 'M') num[6]++;
    }
    /*for(int i = 0;i<7;i++)
    {
        printf("%d\n",num[i]);
    }*/
    return num;
}

// This func extends the subtractive forms to normal representation
// Only following forms are possible
// IV->IIII, IX->VIIII, XL->XXXX, XC->LXXXX, CD->CCCC, CM->DCCCC
char *Extend(char *var)
{
    char *ExVar = (char *)malloc(sizeof(char));
    int len = 0;
    for(int i = 0;var[i] != '\0';i++)
    {
        if(ConvertLetterToInt(var[i]) < ConvertLetterToInt(var[i+1]))
        {
            if (var[i] == 'I' && var[i+1] == 'V')
            {
                ExVar[len] = 'I'; len++;
                ExVar[len] = 'I'; len++;
                ExVar[len] = 'I'; len++;
                ExVar[len] = 'I'; len++;
            }
            else if (var[i] == 'I' && var[i+1] == 'X')
            {
                ExVar[len] = 'V'; len++;
                ExVar[len] = 'I'; len++;
                ExVar[len] = 'I'; len++;
                ExVar[len] = 'I'; len++;
                ExVar[len] = 'I'; len++;
            }
            else if (var[i] == 'X' && var[i+1] == 'L')
            {
                ExVar[len] = 'X'; len++;
                ExVar[len] = 'X'; len++;
                ExVar[len] = 'X'; len++;
                ExVar[len] = 'X'; len++;
            }
            else if (var[i] == 'X' && var[i+1] == 'C')
            {
                ExVar[len] = 'L'; len++;
                ExVar[len] = 'X'; len++;
                ExVar[len] = 'X'; len++;
                ExVar[len] = 'X'; len++;
                ExVar[len] = 'X'; len++;
            }
            else if (var[i] == 'C' && var[i+1] == 'D')
            {
                ExVar[len] = 'C'; len++;
                ExVar[len] = 'C'; len++;
                ExVar[len] = 'C'; len++;
                ExVar[len] = 'C'; len++;
            }
            else if (var[i] == 'C' && var[i+1] == 'M')
            {
                ExVar[len] = 'D'; len++;
                ExVar[len] = 'C'; len++;
                ExVar[len] = 'C'; len++;
                ExVar[len] = 'C'; len++;
                ExVar[len] = 'C'; len++;
            }
            i++;
        }
        else
        {
            ExVar[len] = var[i];
            len++;
        }
    }
    ExVar[len] = '\0';
    /*for(int i = 0;i<len;i++)
    {
        printf("%c",ExVar[i]);
    }
    printf("\n");*/
    return ExVar;
}

// This function reverses the operation of substituting subtractives
// For example CCCCLXXXX becomes CDXC after grouping (reverse of what we are doing in Extend function)
char *Group(char *var)
{
    char *OrderRez = Combine(var);
    int *numOrderRez = Enum(OrderRez);
    char *FinalRez = (char *)malloc(sizeof(char));
    
    int len = 0;
    for(int j = 0;j<numOrderRez[6];j++)
    {
        FinalRez[len] = 'M'; len++;
    }
    numOrderRez[6] = 0;
    if(numOrderRez[5] == 1 && numOrderRez[4] == 4)
    {
        FinalRez[len] = 'C'; len++;
        FinalRez[len] = 'M'; len++;
        numOrderRez[5] = 0;
        numOrderRez[4] = 0;
    }
    else
    {
        for(int j = 0;j<numOrderRez[5];j++)
        {
            FinalRez[len] = 'D'; len++;
        }
        numOrderRez[5] = 0;
    }
    if(numOrderRez[4] == 4)
    {
	FinalRez[len] = 'C'; len++;
        FinalRez[len] = 'D'; len++;
        numOrderRez[4] = 0;
    }
    else
    {
        for(int j = 0;j<numOrderRez[4];j++)
        {
            FinalRez[len] = 'C'; len++;
        }
        numOrderRez[4] = 0;
    }
    if(numOrderRez[3] == 1 && numOrderRez[2] == 4)
    {
        FinalRez[len] = 'X'; len++;
        FinalRez[len] = 'C'; len++;
        numOrderRez[3] = 0;
        numOrderRez[2] = 0;
    }
    else
    {
        for(int j = 0;j<numOrderRez[3];j++)
        {
            FinalRez[len] = 'L'; len++;
        }
        numOrderRez[3] = 0;
    }
    if(numOrderRez[2] == 4)
    {
        FinalRez[len] = 'X'; len++;
        FinalRez[len] = 'L'; len++;
        numOrderRez[2] = 0;
    }
    else
    {
        for(int j = 0;j<numOrderRez[2];j++)
        {
            FinalRez[len] = 'X'; len++;
        }
        numOrderRez[2] = 0;
    }
    if(numOrderRez[1] == 1 && numOrderRez[0] == 4)
    {
        FinalRez[len] = 'I'; len++;
        FinalRez[len] = 'X'; len++;
        numOrderRez[1] = 0;
        numOrderRez[0] = 0;
    }
    else
    {
        for(int j = 0;j<numOrderRez[1];j++)
        {
            FinalRez[len] = 'V'; len++;
        }
        numOrderRez[1] = 0;
    }
    if(numOrderRez[0] == 4)
    {
        FinalRez[len] = 'I'; len++;
        FinalRez[len] = 'V'; len++;
        numOrderRez[0] = 0;
    }
    else
    {
        for(int j = 0;j<numOrderRez[0];j++)
        {
            FinalRez[len] = 'I'; len++;
        }
        numOrderRez[0] = 0;
    }
    FinalRez[len] = '\0';
    return FinalRez;
//    printf("%d\n",ConvertToInt(rez));
}

// This function groups small Roman literals to larger Roman literals
// For example DDCCXIIII->MCCXIIII
char *Combine(char *var)
{
    int *numRez = Enum(var);
    char *OrderRez = (char *)malloc(sizeof(char));
    int len = 0;
    for(int i = 0;i<7;i++)
    {
        if(numRez[i] >= 5 && i%2 == 0)
        {
            numRez[i] = numRez[i] - 5;
            numRez[i+1]++;
        }
        if(numRez[i] == 2 && i%2 == 1)
        {
            numRez[i] = numRez[i] - 5;
            numRez[i+1]++;
        }
    }

    char *x = "IVXLCDM";
    for(int i = 6;i>=0;i--)
    {
        for(int j = 0;j<numRez[i];j++)
        {
            OrderRez[len] = x[i];
            len++;
        }
    }
    OrderRez[len] = '\0';
    /*for(int i = 0;i<len;i++)
    {
        printf("%c,",OrderRez[i]);
    }
    printf("\n");*/
    return OrderRez;
}

int ConvertRomanToInt(char *arg)
{
    int rez = 0;
    int mult = 0;
    for(int i = 0;arg[i] != '\0';i++)
    {
        if(ConvertLetterToInt(arg[i]) < ConvertLetterToInt(arg[i+1]))
        {
            mult = -1;
        }
        else
        {
            mult = 1;
        }
        rez = rez + mult*ConvertLetterToInt(arg[i]);
    }
    return rez;
}

// This func converts each roman literal to equivalent decimal val
int ConvertLetterToInt(char arg) {
    if (arg == 'I'){
        return 1;
    }
    else if(arg == 'V'){
        return 5;
    }
    else if(arg == 'X'){
        return 10;
    }
    else if(arg == 'L'){
        return 50;
    }
    else if(arg == 'C'){
        return 100;
    }
    else if(arg == 'D'){
        return 500;
    }
    else if(arg == 'M'){
        return 1000;
    }
    return 0;
}

char *calc_arg(Variable *v, int x) {
    if(x == 1) {
        return v->arg1;
    }
    if(x == 2) {
        return v->arg2;
    }
}

void var_free(Variable *v) {
    free(v);
}
