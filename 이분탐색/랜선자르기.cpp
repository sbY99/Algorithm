#include <iostream>
#include <math.h>

using namespace std;

typedef long long ll;

ll K, N;
ll arr[10001];

void init();
void input();
bool isPossible(ll n);

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> K >> N;
    for (ll i = 0; i < K; i++)
    {
        cin >> arr[i];
    }
}

bool isPossible(ll n)
{
    ll part_sum = 0;

    for (ll i = 0; i < K; i++)
    {
        part_sum += (arr[i] / n);
        if (part_sum >= N)
        {
            return true;
        }
    }
    return false;
}

void solve()
{
    ll left = 0;
    ll right = pow(2, 31) - 1;
    ll mid, num;

    while (left <= right)
    {
        mid = (left + right) / 2;

        if (isPossible(mid))
        {
            num = left;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout << right;
}

int main()
{
    init();
    input();
    solve();

    return 0;
}