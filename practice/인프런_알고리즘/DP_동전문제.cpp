#include <iostream>
#include <algorithm>
using namespace std;
/*
#define X -1

int main()
{
    //0~5000원
    //3,5원으로 지불해야함
    //dp[n]은 n원을 지불하는데 가능한 동전의 최소 개수를 의미함


    //0원은 0, 1,2,4원은 불가능하므로 -1
    //3,5는 1개이므로 1
    int dp[5001] = {0, X, X, 1, X, 1};
    int n;
    cin >> n;

    //bottom up 방식
    //밑에서부터 값을 저장하면서 필요없는 분기를 없애줌
    for (int i = 6; i <= n; i++)
    {
        //dp[i]는 dp[i-3]+1, dp[i-5]+1로 나뉘는데,
        //둘다 X라면 dp는 X임.
        if (dp[i - 3] == X && dp[i - 5] == X)
        {
            dp[i] = X;
            continue;
        }
        //둘 중 하나만 X라면
        //그 중 큰 값(의미 있는 값) +1이 dp 값이 됨.
        if (dp[i - 3] == X || dp[i - 5] == X)
        {
            dp[i] = max(dp[i - 3] + 1, dp[i - 5] + 1);
            continue;
        }
        //둘 다 가능하다면
        //둘 중 작은 값으로 구성이 됨(최소 동전 개수 이므로)
        dp[i] = min(dp[i - 3] + 1, dp[i - 5] + 1);
    }

    cout << dp[n];
}
*/

#define X 5000
int main()
{
    int dp[5001] = {0, X, X, 1, X, 1};
    int n;
    cin >> n;
    for (int i = 6; i <= n; i++)
    {
        dp[i] = min(dp[i - 3] + 1, dp[i - 5] + 1);
    }
    if (dp[n] >= X)
    {
        cout << -1;
    }
    else
    {
        cout << dp[n];
    }
    return 0;
}