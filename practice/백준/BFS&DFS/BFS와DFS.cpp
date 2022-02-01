#include <iostream>

using namespace std;
int N, M, V;

void dfs(int node);
void bfs(int node);
int Graph[1001][1001];

int main()
{
    cin >> N >> M >> V;
    int n1, n2;
    for (int i = 0; i < M; i++)
    {
        scanf("%d %d", &n1, &n2);
        Graph[n1][n2] = 1;
        Graph[n2][n1] = 1;
    }
    dfs(V);
    printf("\n");
    bfs(V);
    return 0;
}

int Stack[100001];
int Dlist[10001];
int idx;

void dfs(int node)
{
    bool visited[1001] = {false};
    int Top = -1;
    idx = -1;

    Stack[++Top] = node;

    while (Top != -1)
    {
        int curr = Stack[Top--];

        if (!visited[curr])
        {
            visited[curr] = true;
            Dlist[++idx] = curr;

            for (int i = N; i >= 0; i--)
            {
                if (!visited[i] && Graph[curr][i])
                {
                    Stack[++Top] = i;
                }
            }
        }
    }

    for (int i = 0; i <= idx; i++)
    {
        printf("%d ", Dlist[i]);
    }
}

int Queue[100001];
int Qlist[10001];

void bfs(int node)
{
    bool visited[10001] = {false};
    int front = -1;
    int rear = -1;
    idx = -1;

    Queue[++rear] = node;
    visited[node] = true;
    Qlist[++idx] = node;

    while (front != rear)
    {
        int curr = Queue[++front];

        for (int next = 0; next <= N; next++)
        {
            if (!visited[next] && Graph[curr][next])
            {
                Queue[++rear] = next;
                visited[next] = true;
                Qlist[++idx] = next;
            }
        }
    }

    for (int i = 0; i <= idx; i++)
    {
        printf("%d ", Qlist[i]);
    }
}