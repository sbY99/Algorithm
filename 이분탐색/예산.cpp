#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int result;
int arr[10001];

bool isPossible(int num)
{
    int sum = 0;
    int cnt = 0;

    while (cnt < N)
    {
        if (arr[cnt] > num)
        {
            break;
        }
        else
        {
            sum += arr[cnt];
            cnt++;
        }
    }

    sum += ((N - cnt) * num);

    if (sum <= M)
    {
        return true;
    }

    return false;
}

void solve()
{
    sort(arr, arr + N);

    int left = 0;
    int right = 1000000000;
    int mid;

    while (left <= right)
    {
        mid = (left + right) / 2;

        if (isPossible(mid))
        {
            left = mid + 1;
            result = mid;
        }
        else
        {
            right = mid - 1;
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    cin >> M;

    solve();

    if (arr[N - 1] < result)
    {
        result = arr[N - 1];
    }
    cout << result;

    return 0;
}
