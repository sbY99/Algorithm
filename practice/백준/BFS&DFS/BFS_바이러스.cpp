#include <iostream>

using namespace std;

void dfs(int n);

int N, M;
int Graph[101][101];
int Count;

int main()
{
    scanf("%d", &N);
    scanf("%d", &M);
    int n1, n2;
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d", &n1, &n2);
        Graph[n1][n2] = 1;
        Graph[n2][n1] = 1;
    }
    dfs(1);
    printf("%d", Count - 1);
    return 0;
}

bool visited[101];

void dfs(int n)
{
    visited[n] = true;
    Count++;

    for (int next = 0; next <= N; next++)
    {
        if (!visited[next] && Graph[n][next])
        {
            dfs(next);
        }
    }
}
