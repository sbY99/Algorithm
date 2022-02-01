#include <iostream>
#include <algorithm>
using namespace std;

int M, N, K;
int Count;
void dfs(int x, int y);
int grid[51][51];

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        Count = 0;
        //가로길이, 세로길이, 배추 개수
        cin >> M >> N >> K;

        //0<=x,y<=49

        for (int i = 0; i < K; i++)
        {
            int x, y;
            scanf("%d %d", &x, &y);
            grid[y][x] = 1;
        }

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                if (grid[i][j] == 1)
                {
                    //i가 y, j가 x
                    dfs(j, i);
                    Count++;
                }
            }
        }

        printf("%d\n", Count);
    }

    return 0;
}

void dfs(int x, int y)
{
    grid[y][x] = 2;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!(0 <= nx && nx < M && 0 <= ny && ny < N))
        {
            continue;
        }
        if (grid[ny][nx] == 1)
        {
            dfs(nx, ny);
        }
    }
}