#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

int N, K;

void init();
void input();
int count(int num);
void solve();

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> N >> K;
}

int count(int num)
{
    int cnt = 0;
    for (int i = 1; i <= N; i++)
    {
        cnt += min(N, num / i);
    }
    return cnt;
}

void solve()
{
    int start = 1;
    int end = min(pow(10, 9), pow(N, 2));
    int mid, cnt, result;

    while (start <= end)
    {
        mid = (start + end) / 2;
        cnt = count(mid);

        if (cnt < K)
        {
            start = mid + 1;
        }
        else if (cnt > K)
        {
            end = mid - 1;
            result = mid;
        }
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