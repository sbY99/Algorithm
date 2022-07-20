#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int x;
    int y;
} point;

int N;

void swap(point *arr, int i, int j);
void quicksort(point *arr, int low, int high);
int partition(point *arr, int low, int high);

void swap(point *arr, int i, int j)
{
    point temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void quicksort(point *arr, int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}

int partition(point *arr, int low, int high)
{
    int pivotIdx = (rand() % (high - low + 1)) + low;
    point pivot = arr[pivotIdx];

    swap(arr, pivotIdx, high);

    int start = low;

    for (int i = low; i < high; i++)
    {
        if (arr[i].y < pivot.y)
        {
            swap(arr, start, i);
            start++;
        }
        else if (arr[i].y == pivot.y)
        {
            if (arr[i].x < pivot.x)
            {
                swap(arr, start, i);
                start++;
            }
        }
    }
    swap(arr, start, high);
    return start;
}

int main(void)
{
    scanf("%d", &N);

    point *arr = (point *)malloc(sizeof(point) * N);
    for (int i = 0; i < N; i++)
        scanf("%d %d", &arr[i].x, &arr[i].y);

    quicksort(arr, 0, N - 1);

    for (int i = 0; i < N; i++)
        printf("%d %d\n", arr[i].x, arr[i].y);

    return 0;
}