#include <iostream>
#include <cstring>

using namespace std;

int N, M;
int Relation[101][101];
int KB[101];

void bfs(int n)
{
    int Queue[101];
    int Dlist[101];
    bool visited[101];

    memset(visited, false, sizeof(visited));
    int Front = -1, Rear = -1;
    int dFront = -1, dRear = -1;

    // n노드 방문 예정 목록에 추가
    Queue[++Rear] = n;
    Dlist[++dRear] = 0;
    visited[n] = true;

    //전부다 방문할 때 까지 실행
    while (Front != Rear)
    {
        //맨 앞 노드 방문
        int curr = Queue[++Front];
        // n에 대한 케빈베이컨 값을 추가
        KB[n] += Dlist[++dFront];

        for (int i = 1; i <= N; i++)
        {
            int temp = Dlist[dFront];
            //방문하지 않았고, 관계가 있다면
            if (visited[i] == false && Relation[curr][i])
            {
                //방문 예정 목록에 추가
                Queue[++Rear] = i;
                Dlist[++dRear] = temp + 1;
                visited[i] = true;
            }
        }
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int u1, u2;
        scanf("%d %d", &u1, &u2);
        Relation[u1][u2] = 1;
        Relation[u2][u1] = 1;
    }
    for (int i = 1; i <= N; i++)
    {
        bfs(i);
    }

    int idx = 1;
    int min = 101;
    for (int i = 1; i <= N; i++)
    {
        if (min > KB[i])
        {
            idx = i;
            min = KB[i];
        }
    }
    printf("%d", idx);
    return 0;
}