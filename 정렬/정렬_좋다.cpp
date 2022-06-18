#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>

using namespace std;

void swap(int *arr, int i, int j);
void quicksort(int *arr, int low, int high);
int partition(int *arr, int low, int high);
void solve(int *arr);
int N;

void swap(int *arr, int i, int j)
{
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
void quicksort(int *arr, int low, int high)
{
    if (low < high)
    {
        int p = partition(arr, low, high);
        quicksort(arr, low, p - 1);
        quicksort(arr, p + 1, high);
    }
}
int partition(int *arr, int low, int high)
{
    int pivotIdx = (rand() % (high - low + 1)) + low;
    int pivot = arr[pivotIdx];
    swap(arr, pivotIdx, high);

    int start = low;

    for (int i = low; i < high; i++)
    {
        if (arr[i] < pivot)
        {
            swap(arr, i, start);
            start++;
        }
    }
    swap(arr, start, high);
    return start;
}

void solve(int *arr)
{
    int cnt = 0;

    for (int i = 0; i < N; i++)
    {
        int target = arr[i];
        int start = 0;
        int end = N - 1;

        while (start < end)
        {
            int sum = arr[start] + arr[end];
            if (sum == target)
            {
                if ((i != start) && (i != end))
                {
                    cnt++;
                    break;
                }
                else if (i == start)
                {
                    start++;
                }
                else if (i == end)
                {
                    end--;
                }
            }
            else if (sum < target)
            {
                start++;
            }
            else
            {
                end--;
            }
        }
    }
    cout << cnt;
}

int main()
{
    srand(time(NULL));
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    int arr[2001];

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    quicksort(arr, 0, N - 1);

    solve(arr);

    return 0;
}