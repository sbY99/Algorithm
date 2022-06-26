#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
typedef long long ll;

int M, N;
ll MAX;
ll arr[100001];

void init();
void input();
ll cntPeople(ll num);
void solve();

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    MAX = 0;
}

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
        MAX = max(arr[i], MAX);
    }
}

ll cntPeople(ll num)
{
    ll cnt = 0;

    for (int i = 0; i < N; i++)
    {
        cnt += num / arr[i];
    }
    return cnt;
}

void solve()
{
    ll left = 1;
    ll right = MAX * M;
    ll mid, cnt;

    ll result = 0;

    while (left <= right)
    {
        mid = (left + right) / 2;
        cnt = cntPeople(mid);

        if (cnt < M)
        {
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
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