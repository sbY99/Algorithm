#include <iostream>
#include <map>
#include <random>
#include <time.h>
#include <algorithm>

using namespace std;

void swap(int *arr, int i, int j);
void quicksort(int *arr, int low, int high);
int partition(int *arr, int low, int high);
void solve(int *arr1, int *arr2);
void input();
void init();
void result_init(int *arr);
void output();

int N, M;
map<int, int> result;
int arr1[500001];
int arr2[500001];
int arr3[500001];

void init()
{
    srand(time(NULL));
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void result_init(int *arr)
{
    for (int i = 0; i < M; i++)
    {
        result[arr[i]] = 0;
    }
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

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr1[i];
    }

    cin >> M;
    for (int i = 0; i < M; i++)
    {
        cin >> arr2[i];
        arr3[i] = arr2[i];
    }
}

void solve(int *arr1, int *arr2)
{
    int arr1_idx = 0;
    int arr2_idx = 0;

    result_init(arr2);

    while (arr1_idx < N && arr2_idx < M)
    {
        if (arr1[arr1_idx] == arr2[arr2_idx])
        {
            result[arr2[arr2_idx]]++;
            arr1_idx++;
        }
        else if (arr1[arr1_idx] < arr2[arr2_idx])
        {
            arr1_idx++;
        }
        else
        {
            arr2_idx++;
        }
    }
}

void output()
{
    for (int i = 0; i < M; i++)
    {
        cout << result[arr3[i]] << " ";
    }
}

int main()
{
    init();
    input();
    // quicksort(arr1, 0, N - 1);
    // quicksort(arr2, 0, M - 1);
    sort(arr1, arr1 + N);
    sort(arr2, arr2 + M);
    solve(arr1, arr2);
    output();
}