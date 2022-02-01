#include <stdio.h>
#include <stdlib.h>

typedef struct _word
{
    char array[51];
    int len;
} Word;

int main()
{
    int n;
    scanf("%d", &n);
    Word *arr = malloc(sizeof(Word) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%s", arr[i].array);
        arr[i].len = strlen(arr[i].array);
    }
}