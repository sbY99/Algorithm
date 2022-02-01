#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

extern void bfs_init(int N, int map[10][10]);
extern int bfs(int x1, int y1, int x2, int y2);

static int test_bfs()
{
    int N;
    int map[10][10];
    scanf("%d", &N);
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            scanf("%d", &map[i][j]);
        }
    }
    bfs_init(N, map);
    int M;
    int score = 100;
    scanf("%d", &M);
    for (int i = 0; i < M; ++i)
    {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        int result = bfs(x1, y1, x2, y2);
        int dist;
        scanf("%d", &dist);
        if (result != dist)
            score = 0;
    }
    return score;
}

int main()
{
    setbuf(stdout, NULL);

    printf("#total score : %d\n", test_bfs());

    return 0;
}

////////////////////////////////////////////////////

using namespace std;

struct XY
{
    int x;
    int y;
};

int Reset[11][11];
int Grid[11][11];
int N;

void bfs_init(int map_size, int map[10][10])
{
    N = map_size;
    //벽을 100으로 바꿔줌
    //0~9를 1~10으로 바꿔줌
    for (int i = 1; i <= map_size; i++)
    {
        for (int j = 1; j <= map_size; j++)
        {
            Grid[i][j] = map[i - 1][j - 1];
            Reset[i][j] = map[i - 1][j - 1];
        }
    }
}

//x는 열 y는 행, 좌상좌표는 x=1 y=1
//x=3 y=5 -> Grid[5][3] 즉, Grid[y][x]
int bfs(int x1, int y1, int x2, int y2)
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            Grid[i][j] = Reset[i][j];
        }
    }

    XY Queue[100];
    int Front, Rear;
    Front = Rear = -1;

    XY Start;
    Start.x = x1;
    Start.y = y1;
    Queue[++Rear] = Start;

    while (Front != Rear)
    {
        Front++;
        int curr_x = Queue[Front].x;
        int curr_y = Queue[Front].y;

        if (curr_x == x2 && curr_y == y2)
        {
            return Grid[y2][x2];
        }

        int dx[] = {-1, 0, 0, 1};
        int dy[] = {0, 1, -1, 0};

        for (int i = 0; i < 4; i++)
        {
            int next_x = curr_x + dx[i];
            int next_y = curr_y + dy[i];
            //범위를 벗어난다면(1~max_size)
            if (!(1 <= next_x && next_x <= N && 1 <= next_y && next_y <= N))
            {
                continue;
            }
            //이미 방문했다면, 혹은 벽이 있다면(0이 아니라면)
            if (Grid[next_y][next_x] != 0)
            {
                continue;
            }
            //방문이 가능하면
            Rear++;
            Queue[Rear].x = next_x;
            Queue[Rear].y = next_y;

            Grid[next_y][next_x] = Grid[curr_y][curr_x] + 1;
        }
    }

    return -1;
}