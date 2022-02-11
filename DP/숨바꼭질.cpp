#include <iostream>
#include <queue>

using namespace std;

int N, K;
int dp[100001];
queue<int> q;

void bfs()
{
    q.push(N);
    dp[N] = 0;
    while (q.size())
    {
        int curr = q.front();
        q.pop();
        int depth = dp[curr] + 1;
        if (curr - 1 == K || curr + 1 == K || curr * 2 == K)
        {
            dp[K] = depth;
            break;
        }

        if (curr - 1 >= 0)
        {
            if (dp[curr - 1] > depth)
            {
                q.push(curr - 1);
                dp[curr - 1] = depth;
            }
        }

        if (curr + 1 <= 100000)
        {
            if (dp[curr + 1] > depth)
            {
                q.push(curr + 1);
                dp[curr + 1] = depth;
            }
        }

        if (curr * 2 <= 100000)
        {
            if (dp[curr * 2] > depth)
            {
                q.push(curr * 2);
                dp[curr * 2] = depth;
            }
        }
    }
}

int main()
{
    cin >> N >> K;
    for (int i = 0; i <= 100000; i++)
    {
        dp[i] = 100000;
    }
    if (N == K)
        printf("0");
    else
    {
        bfs();
        printf("%d", dp[K]);
    }

    return 0;
}
