#include <iostream>

#define MAX 1001
using namespace std;

int dp[MAX];

int main()
{
    int n;
    cin >> n;
    dp[1] = 1, dp[2] = 3;
    for (int i = 3; i <= n; i++)
    {
        dp[i] = (dp[i - 2] * 2 + dp[i - 1]) % 10007;
    }
    printf("%d", dp[n]);
    return 0;
}