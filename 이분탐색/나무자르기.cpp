#include <iostream>

using namespace std;
int N;
long long M;
long long trees[1000001];

void init();
void input();

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

bool isPossible(unsigned int height)
{
    unsigned int taken = 0;
    for (int i = 0; i < N; i++)
    {
        if (trees[i] >= height)
            taken += (trees[i] - height);
        if (taken >= M)
            return true;
    }
    return false;
}
int solve()
{
    unsigned int left = 0, right = 1000000000;
    unsigned int mid, result;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (isPossible(mid))
        {
            result = mid;
            left = mid + 1;
        }
        else
        {
            right = mid - 1;
        }
    }
    cout << result;
}
int main()
{
    init();
    input();
    solve();
}