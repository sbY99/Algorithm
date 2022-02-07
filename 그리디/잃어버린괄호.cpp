#include <iostream>
#include <string.h>

using namespace std;

char expression[51];
int numList[51];
char opList[51];
int result;

int main()
{
    scanf("%s", expression);
    int num = 0;
    int num_idx = -1;
    int op_idx = -1;
    for (int i = 0; i < strlen(expression); i++)
    {
        if (isdigit(expression[i]))
        {
            num = num * 10 + (expression[i] - '0');
        }
        else
        {
            numList[++num_idx] = num;
            opList[++op_idx] = expression[i];
            num = 0;
        }
    }
    numList[++num_idx] = num;

    int i = -1, j = -1;
    result = numList[++i];

    while (j < op_idx)
    {
        if (opList[++j] == '+')
        {
            result += numList[++i];
        }
        else
        {
            result -= numList[++i];
            break;
        }
    }

    while (j < op_idx)
    {
        result -= numList[++i];
        j++;
    }

    printf("%d", result);
    return 0;
}