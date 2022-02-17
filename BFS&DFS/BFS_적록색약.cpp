#include <iostream>
#include <cstring>
#include <string>
#include <queue>

using namespace std;
#define Max 101

struct XY
{
    int x;
    int y;
};

// 0:R 1:G 2:B
int grid[Max][Max];
bool visited[Max][Max];
queue<struct XY> q;

// 0:R,G 1:B
int RGgrid[Max][Max];
bool RGvisited[Max][Max];

int N;
int r1, r2;

void init()
{
    memset(visited, false, sizeof(visited));
    memset(RGvisited, false, sizeof(RGvisited));
}

// 0,1,2(색깔) 입력 받음
void bfs(int num)
{
    while (q.size() > 0)
    {
        XY curr = q.front();
        q.pop();

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (!(0 <= nx && nx < N && 0 <= ny && ny < N))
            {
                continue;
            }
            if (visited[ny][nx] == true)
            {
                continue;
            }
            if (grid[ny][nx] != num)
            {
                continue;
            }
            visited[ny][nx] = true;
            XY next;
            next.x = nx;
            next.y = ny;
            q.push(next);
        }
    }
}

// 0,1(색깔) 입력 받음
void RGbfs(int num)
{
    while (q.size() > 0)
    {
        XY curr = q.front();
        q.pop();

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (!(0 <= nx && nx < N && 0 <= ny && ny < N))
            {
                continue;
            }
            if (RGvisited[ny][nx] == true)
            {
                continue;
            }
            if (RGgrid[ny][nx] != num)
            {
                continue;
            }
            RGvisited[ny][nx] = true;
            XY next;
            next.x = nx;
            next.y = ny;
            q.push(next);
        }
    }
}

void Solve()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (visited[i][j] == false)
            {
                XY xy;
                xy.x = j;
                xy.y = i;
                q.push(xy);

                visited[i][j] = true;
                r1++;
                bfs(grid[i][j]);
            }
        }
    }
}

void RGSolve()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (RGvisited[i][j] == false)
            {
                XY xy;
                xy.x = j;
                xy.y = i;
                q.push(xy);

                RGvisited[i][j] = true;
                r2++;
                RGbfs(RGgrid[i][j]);
            }
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    init();

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string input;
        cin >> input;
        for (int j = 0; j < N; j++)
        {
            if (input[j] == 'R')
            {
                grid[i][j] = 0;
                RGgrid[i][j] = 0;
            }
            else if (input[j] == 'G')
            {
                grid[i][j] = 1;
                RGgrid[i][j] = 0;
            }
            else
            {
                grid[i][j] = 2;
                RGgrid[i][j] = 1;
            }
        }
    }
    Solve();
    RGSolve();
    printf("%d %d", r1, r2);

    return 0;
}