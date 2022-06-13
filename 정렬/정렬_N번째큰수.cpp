#include <iostream>

using namespace std;

void swap(int *arr, int i, int j);
void quicksort(int *arr, int low, int high);
int partition(int *arr, int low, int high);

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
            swap(arr, start, i);
            start++;
        }
    }
    swap(arr, start, high);
    return start;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    int *arr1 = new int[N * 2];

    for (int i = 0; i < N * 2; i++)
    {
        cin >> arr1[i];
    }
    quicksort(arr1, 0, N * 2 - 1);

    for (int i = 0; i < N - 2; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> arr1[j];
        }
        quicksort(arr1, 0, N * 2 - 1);
    }

    cout << arr1[N];

    delete[] arr1;
    return 0;
}