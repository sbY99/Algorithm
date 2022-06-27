#include <iostream>
#include <algorithm>

using namespace std;

void init();
void input();
bool isPossible(int num);
void solve();

int N, C;
int arr[200001];

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> N >> C;

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
}

bool isPossible(int num)
{
    // 간격은 C-1개 이므로 1부터
    int cnt = 1;
    int prev = arr[0];

    for (int i = 1; i < N; i++)
    {
        if (arr[i] - prev >= num)
        {
            cnt++;
            prev = arr[i];
        }
    }

    if (cnt >= C)
        return true;
    return false;
}

void solve()
{
    sort(arr, arr + N);

    // 최소거리, 최대거리
    int low = 1;
    int high = arr[N - 1] - arr[0];
    int result = 0;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (isPossible(mid))
        {
            result = max(result, mid);
            low = mid + 1;
        }
        else
            high = mid - 1;
    }

    cout << result;
}

int main()
{
    init();
    input();
    solve();

    return 0;
}