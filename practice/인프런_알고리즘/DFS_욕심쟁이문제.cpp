#include <iostream>
#include <algorithm>
using namespace std;

int n;
int field[510][510];
int dp[510][510];

int dfs(int cx, int cy)
{

    if (dp[cx][cy])
        return dp[cx][cy];

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        int nx = cx + dx[i];
        int ny = cy + dy[i];
        if (!(0 <= nx && nx < n && 0 <= ny && ny < n))
            continue;
        if (field[cx][cy] >= field[nx][ny])
            continue;
        dp[cx][cy] = max(dp[cx][cy], dfs(nx, ny) + 1);
    }
    return dp[cx][cy];
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &field[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (dp[i][j] == 0)
            {
                dp[i][j] = dfs(i, j);
            }
        }
    }
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (max < dp[i][j])
                max = dp[i][j];
        }
    }
    printf("%d", max + 1);
}
