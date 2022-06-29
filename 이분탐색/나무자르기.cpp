#include <iostream>

using namespace std;
typedef long long ll;

int N;
ll M;
ll trees[1000001];

void init();
void input();
bool isPossible(ll height);
void solve();

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> trees[i];
}

bool isPossible(ll height)
{
    ll taken = 0;
    for (int i = 0; i < N; i++)
    {
        if (trees[i] >= height)
            taken += (trees[i] - height);
        if (taken >= M)
            return true;
    }
    return false;
}

void solve()
{
    ll left = 0, right = 1000000000;
    ll mid, result;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (isPossible(mid))
        {
            result = mid;
            left = mid + 1;
        }
        else
            right = mid - 1;
    }
    cout << result;
}
int main()
{
    init();
    input();
    solve();
}