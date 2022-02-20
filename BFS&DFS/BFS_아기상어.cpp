#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
#define Max 20 + 1

struct XY
{
    int t;
    int x;
    int y;
};

int N;
int sharkSize;
int sharkEat;
XY sharkLoc;
int totalTime;
bool isEnd;
int Grid[Max][Max];

struct cmp
{
    bool operator()(XY n1, XY n2)
    {
        if (n1.t > n2.t)
        {
            return true;
        }
        else if (n1.t == n2.t)
        {
            if (n1.y > n2.y)
            {
                return true;
            }
            else if (n1.y == n2.y)
            {
                if (n1.x > n2.x)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
        return false;
    }
};

void move2Eat()
{
    priority_queue<struct XY, vector<XY>, cmp> q;

    q.push(sharkLoc);

    int timeGrid[Max][Max];
    bool visited[Max][Max];
    memset(visited, false, sizeof(visited));
    memset(timeGrid, 0, sizeof(timeGrid));
    visited[sharkLoc.y][sharkLoc.x] = true;

    while (!q.empty())
    {
        XY curr = q.top();
        q.pop();

        // 상어의 크기가 물고기 크기보다 크면
        // 먹을 수 있음
        if (Grid[curr.y][curr.x] < sharkSize && Grid[curr.y][curr.x] != 0)
        {
            // 물고기를 먹으러 갔으므로
            // 상어 위치 변경
            sharkLoc.x = curr.x;
            sharkLoc.y = curr.y;
            sharkEat++;

            // 자신의 크기와 같은 수의 물고기를 먹으면
            // 크기를 키우고 먹은 물고기 수는 초기화
            if (sharkEat == sharkSize)
            {
                sharkEat = 0;
                sharkSize++;
            }
            // 먹힌 물고기는 0이됨
            Grid[curr.y][curr.x] = 0;

            // 물고기 이동까지 걸린 시간을 더해줌
            totalTime += timeGrid[curr.y][curr.x];
            isEnd = false;
            return;
        }

        //가까운 물고기가 많다면
        //맨위 -> 맨 왼쪽
        int dx[] = {0, -1, 1, 0};
        int dy[] = {-1, 0, 0, 1};

        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (!(1 <= nx && nx <= N && 1 <= ny && ny <= N))
            {
                continue;
            }

            if (visited[ny][nx] == true)
            {
                continue;
            }

            // 상어의 크기가 물고기 크기와 같거나, 칸이 0이면
            // 이동만 할 수 있음
            if (Grid[ny][nx] <= sharkSize || Grid[ny][nx] == 0)
            {
                XY temp;
                temp.x = nx;
                temp.y = ny;
                temp.t = timeGrid[curr.y][curr.x] + 1;
                // prioirty queue에 우선적으로 Push
                q.push(temp);

                visited[ny][nx] = true;
                timeGrid[ny][nx] = timeGrid[curr.y][curr.x] + 1;
            }
        }
    }
}

void Solve()
{
    while (1)
    {
        move2Eat();
        if (isEnd == true)
            break;
        isEnd = true;
    }
}

int main()
{
    cin >> N;
    sharkSize = 2;
    isEnd = true;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            scanf("%d", &Grid[i][j]);
            if (Grid[i][j] == 9)
            {
                sharkLoc.x = j;
                sharkLoc.y = i;
                Grid[i][j] = 0;
            }
        }
    }
    Solve();
    printf("%d", totalTime);
}
