#include <stdio.h>
#include <stdlib.h>

//백준 10989번
int main()
{
    int n;
    int arr[10001] = {
        0,
    };
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int num;
        scanf("%d", &num);
        arr[num]++;
    }
    for (int i = 1; i < 10002; i++)
    {
        while (arr[i] != 0)
        {
            printf("%d\n", i);
            arr[i]--;
        }
    }

    return 0;
}