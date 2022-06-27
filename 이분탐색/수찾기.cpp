#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int arr[100001];

void init();
void input();
void solve();
void search(int num, int start, int end);

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
}

void search(int num, int start, int end)
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

void solve()
{
    sort(arr, arr + N);

    cin >> M;

    for (int i = 0; i < M; i++)
    {
        int num;
        cin >> num;

        search(num, 0, N - 1);
    }
}

int main()
{
    init();
    input();
    solve();

    return 0;
}