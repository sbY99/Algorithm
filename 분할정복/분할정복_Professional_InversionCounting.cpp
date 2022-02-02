#include <iostream>
#include <stdio.h>

using namespace std;

int arr[100001];
int sorted[100001];
long long Count;

void merge_sort(int start, int end);
void merge(int start, int mid, int end);

int main(int argc, char **argv)
{
    int test_case;
    int T, N;
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
        Count = 0;

        for (int i = 0; i < N; i++)
        {
            scanf("%d", &arr[i]);
        }
        merge_sort(0, N - 1);
        printf("#%d %lld\n", test_case, Count);
    }
    return 0;
}

void merge_sort(int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        merge_sort(start, mid);
        merge_sort(mid + 1, end);
        merge(start, mid, end);
    }
}

void merge(int start, int mid, int end)
{
    int left = start;
    int right = mid + 1;
    int k = start;
    while (left <= mid && right <= end)
    {
        if (arr[left] < arr[right])
        {
            sorted[k++] = arr[left++];
        }
        //뒤집힌 순서를 바꾸기 때문
        else
        {
            Count += mid - left + 1;
            sorted[k++] = arr[right++];
        }
    }
    if (left > mid)
    {
        for (int i = right; i <= end; i++)
        {
            sorted[k++] = arr[i];
        }
    }
    else
    {
        for (int i = left; i <= mid; i++)
        {
            sorted[k++] = arr[i];
        }
    }

    for (int i = start; i <= end; i++)
    {
        arr[i] = sorted[i];
    }
}