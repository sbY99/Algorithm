/*
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

#define MAX 101
using namespace std;

struct XY
{
    int x;
    int y;
};

queue<struct XY> q;
int grid[MAX][MAX];
int visitedGrid[MAX][MAX];
bool visited[MAX][MAX];

int result;
int N;

void Init()
{
    result = 0;
    memset(grid, 0, sizeof(grid));
    memset(visitedGrid, 0, sizeof(visitedGrid));
    memset(visited, false, sizeof(visited));
}

void Input()
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            char input;
            scanf(" %c", &input);
            grid[i][j] = input - '0';
        }
    }
}

void bfs()
{
    //1,1푸쉬
    q.push({1, 1});
    visited[1][1] = true;

    while (q.size())
    {
        auto c = q.front();
        q.pop();

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++)
        {
            int nx = c.x + dx[i];
            int ny = c.y + dy[i];

            if (!(1 <= nx && nx <= N && 1 <= ny && ny <= N))
            {
                continue;
            }
            if (visited[ny][nx] == false)
            {
                visitedGrid[ny][nx] = grid[ny][nx] + visitedGrid[c.y][c.x];
                visited[ny][nx] = true;
                q.push({nx, ny});
            }
            else
            {
                if (visitedGrid[ny][nx] > grid[ny][nx] + visitedGrid[c.y][c.x])
                {
                    q.push({nx, ny});
                    visitedGrid[ny][nx] = grid[ny][nx] + visitedGrid[c.y][c.x];
                }
            }
        }
    }

    result = visitedGrid[N][N];
}

int main(int argc, char **argv)
{
    int test_case;
    int T;
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        Init();
        cin >> N;
        Input();
        bfs();
        printf("#%d %d\n", test_case, result);
    }
    return 0;
}

*/