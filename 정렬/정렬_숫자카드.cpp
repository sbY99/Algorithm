#include <iostream>
#include <map>
#include <random>
#include <time.h>

using namespace std;

int arr1[500001];
int arr2[500001];
int arr3[500001];

void input();
void swap(int *arr, int i, int j);
void quicksort(int *arr, int low, int high);
int partition(int *arr, int low, int high);
void solve(int *arr1, int *arr2);
int N, M;
map<int, int> result;

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
        int mid = partition(arr, low, high);
        quicksort(arr, low, mid - 1);
        quicksort(arr, mid + 1, high);
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

void solve(int *arr1, int *arr2)
{
    int arr1_idx = 0;
    int arr2_idx = 0;

    while (arr1_idx < N && arr2_idx < M)
    {
        if (arr1[arr1_idx] == arr2[arr2_idx])
        {
            result[arr2[arr2_idx]] = 1;
            arr1_idx++;
            arr2_idx++;
        }
        else if (arr1[arr1_idx] < arr2[arr2_idx])
        {
            arr1_idx++;
        }
        else
        {
            result[arr2[arr2_idx]] = 0;
            arr2_idx++;
        }
    }
}

int main()
{
    input();
    srand(time(NULL));

    quicksort(arr1, 0, N - 1);
    quicksort(arr2, 0, M - 1);
    solve(arr1, arr2);

    for (int i = 0; i < M; i++)
    {
        cout << result[arr3[i]] << " ";
    }

    return 0;
}