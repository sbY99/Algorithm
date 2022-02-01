#include <stdio.h>
#include <stdlib.h>

//백준 1427번
int main()
{
    int arr[10] = {
        0,
    };
    while (1)
    {
        char a;
        scanf("%c", &a);
        if (a == '\n')
            break;
        arr[a - '0']++;
    }
    for (int i = 9; i >= 0; i--)
    {
        while (arr[i] > 0)
        {
            printf("%d", i);
            arr[i]--;
        }
    }
}