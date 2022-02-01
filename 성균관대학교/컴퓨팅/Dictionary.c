#include <stdio.h>
#include <stdlib.h>

int find(int *arr, int k, int l, int r)
{
    if (l > r)
    {
        return -1;
    }
    int mid = (l + r) / 2;

    if (k == arr[mid])
    {
        return mid;
    }

    else if (k < arr[0])
    {
        return -1;
    }
    else if (l == r)
    {
        return mid;
    }
    else if (k < arr[mid])
    {
        if (k >= arr[mid - 1])
        {
            return mid - 1;
        }
        return find(arr, k, l, mid - 2);
    }

    else
    {
        if (k < arr[mid + 1])
        {
            return mid;
        }
        return find(arr, k, mid + 1, r);
    }
}

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int *arr = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    int result = find(arr, k, 0, n - 1);
    printf(" %d", result);

    return 0;
}