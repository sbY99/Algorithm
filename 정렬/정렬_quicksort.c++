#include <iostream>
#define MAX 100001
using namespace std;

int N, K;
int Cnt;
int flag;

void quick_sort(int *arr, int p, int r);
int partition(int *arr, int p, int r);

void quick_sort(int *arr, int p, int r)
{
    if (p < r)
    {
        int q = partition(arr, p, r);
        if (flag == 1)
        {
            return;
        }
        quick_sort(arr, p, q - 1);
        quick_sort(arr, q + 1, r);
    }
}

int partition(int *arr, int p, int r)
{
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++)
    {
        if (arr[j] <= x)
        {

            int temp = arr[++i];

            if (K == Cnt)
            {
                cout << arr[j] << " " << temp;
            }

            arr[i] = arr[j];
            arr[j] = temp;

            Cnt++;
        }
    }

    if (i + 1 != r)
    {

        int temp = arr[i + 1];

        if (K == Cnt)
        {
            cout << arr[r] << " " << temp;
        }

        arr[i + 1] = arr[r];
        arr[r] = temp;

        Cnt++;
    }

    return i + 1;
}

int main()
{
    Cnt = 1;
    int arr[MAX];
    cin >> N >> K;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
    quick_sort(arr, 0, N - 1);

    if (Cnt < K)
    {
        cout << -1;
    }

    return 0;
}