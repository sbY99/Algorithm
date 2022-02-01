/*
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

struct XY
{
    int x;
    int y;
};

int N, M;
queue<struct XY> q;
int grid[101][101];
int Count[101][101];
void bfs();

int main()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        char input[101];
        scanf("%s", input);
        for (int j = 1; j <= M; j++)
        {
            grid[i][j] = input[j - 1] - '0';
        }
    }
    bfs();
}

void bfs()
{
    q.push({1, 1});
    Count[1][1] = 1;
    while (q.size())
    {
        auto c = q.front();
        q.pop();

        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};

        for (int i = 0; i < 4; i++)
        {
            int nx = c.x + dx[i];
            int ny = c.y + dy[i];
            if (!(1 <= nx && nx <= M && 1 <= ny && ny <= N))
            {
                continue;
            }
            if (grid[ny][nx] == 0)
            {
                continue;
            }
            if (Count[ny][nx] != 0)
            {
                continue;
            }
            q.push({nx, ny});
            Count[ny][nx] = Count[c.y][c.x] + 1;
        }
    }

    printf("%d", Count[N][M]);
}

*/