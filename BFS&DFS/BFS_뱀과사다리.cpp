#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
#define Max 100 + 1

int N, M;
int Result;
int S[Max];
int visited[Max];
queue<int> q;

void Solve()
{
    q.push(1);
    memset(visited, -1, sizeof(visited));
    visited[1] = 0;

    while (q.size())
    {
        int curr = q.front();
        q.pop();

        for (int i = 1; i <= 6; i++)
        {
            int next = curr + i;
            if (next > 100)
            {
                continue;
            }
            //사다리 혹은 뱀이면 이동시킴
            if (S[next] != 0)
            {
                next = S[next];
            }
            if (visited[next] == -1)
            {
                visited[next] = visited[curr] + 1;
                q.push(next);
            }
        }
    }
}

int main()
{
    scanf("%d %d", &N, &M);
    //사다리 + 뱀
    for (int i = 0; i < N + M; i++)
    {
        int idx, num;
        // idx에 도착하면 num으로 이동
        scanf("%d %d", &idx, &num);
        S[idx] = num;
    }
    Solve();
    printf("%d", visited[100]);
    return 0;
}