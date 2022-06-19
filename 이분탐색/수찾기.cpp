#include <iostream>
#include <algorithm>

using namespace std;

void search(int *arr, int num, int start, int end)
{
    while (start <= end)
    {
        int mid = (start + end) / 2;

        if (arr[mid] == num)
        {
            cout << "1\n";
            return;
        }
        else if (arr[mid] > num)
        {
            end = mid - 1;
        }
        else
        {
            start = mid + 1;
        }
    }
    cout << "0\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    int arr[100001];
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    sort(arr, arr + N);

    cin >> M;

    for (int i = 0; i < M; i++)
    {
        int num;
        cin >> num;

        search(arr, num, 0, N - 1);
    }

    return 0;
}