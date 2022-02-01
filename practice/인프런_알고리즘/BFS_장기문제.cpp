/*
#include <iostream>
#include <queue>
using namespace std;

struct coor
{
    int x, y;
};

queue<coor> q;

int n, m;
int sx, sy;
int fx, fy;
int grid[310][310];

int main()
{
    scanf("%d%d", &n, &m);
    scanf("%d%d", &sx, &sy);
    scanf("%d%d", &fx, &fy);

    q.push({sx, sy});
    while (q.size() > 0)
    {

        auto c = q.front();
        q.pop();

        if (c.x == fx && c.y == fy)
        {
            printf("%d\n", grid[c.x][c.y]);
            break;
        }

        int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
        int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

        for (int i = 0; i < 8; i++)
        {
            int nx = c.x + dx[i];
            int ny = c.y + dy[i];
            if (!(1 <= nx && nx <= n && 1 <= ny && ny <= m))
                continue;
            if (grid[nx][ny] != 0)
                continue;
            grid[nx][ny] = grid[c.x][c.y] + 1;
            q.push({nx, ny});
        }
    }
}
*/