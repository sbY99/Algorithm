#include <iostream>
#include <algorithm>

using namespace std;

int N, Max;
int T[16];
int P[16];

// N~1까지 들어옴
void solve(int n, int sum)
{
    for (int i = n - 1; i >= 1; i--)
    {
        if (i + T[i] <= n)
        {
            solve(i, sum + P[i]);
        }
    }
    if (sum > Max)
        Max = sum;
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        scanf("%d %d", &T[i], &P[i]);
    }
    for (int i = N; i >= 1; i--)
    {
        if (i + T[i] > N + 1)
            continue;

        solve(i, P[i]);
    }
    printf("%d", Max);
    return 0;
}