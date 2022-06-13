#include <iostream>
#include <time.h>
#include <random>

using namespace std;

void init();
void input();
void swap(int *arr, int i, int j);
void quicksort(int *arr, int low, int high);
int partition(int *arr, int low, int high);
void solve(int *arr);

int N, X;
int seq[100001];

void init()
{
    srand(time(NULL));
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> seq[i];
    }
    cin >> X;
}

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
            swap(arr, start, i);
            start++;
        }
    }
    swap(arr, start, high);
    return start;
}

void solve(int *arr)
{
    int cnt = 0;

    for (int i = 0; i < N - 1; i++)
    {
        if (arr[i] >= X)
        {
            break;
        }
        for (int j = i + 1; j < N; j++)
        {
            if ((arr[i] + arr[j]) == X)
            {
                cnt++;
            }
            else if ((arr[i] + arr[j]) > X)
            {
                break;
            }
        }
    }

    cout << cnt;
}

int main()
{
    init();
    input();
    quicksort(seq, 0, N - 1);
    solve(seq);

    return 0;
}