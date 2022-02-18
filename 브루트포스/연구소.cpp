#include <iostream>
#include <queue>

using namespace std;

struct XY
{
    int x;
    int y;
};

XY initVirous[64];
int initVirousLen;
int N, M;
int Grid[9][9];
int Max;

void copyGrid(int tempGrid[9][9])
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            tempGrid[i][j] = Grid[i][j];
        }
    }
}

//안전 지역 검사
int Check(int tempGrid[9][9])
{
    int Count = 0;

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (tempGrid[i][j] == 0)
                Count++;
        }
    }
    return Count;
}

//바이러스 퍼뜨림
void BFS()
{
    // BFS를 위한 temp 값 생성
    int tempGrid[9][9];
    copyGrid(tempGrid);

    queue<struct XY> Virous;

    for (int i = 0; i < initVirousLen; i++)
    {
        XY virousIdx;
        virousIdx.x = initVirous[i].x;
        virousIdx.y = initVirous[i].y;
        Virous.push(virousIdx);
    }

    while (Virous.size())
    {
        XY curr = Virous.front();
        Virous.pop();

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, 1, -1};

        for (int i = 0; i < 4; i++)
        {
            int nx = curr.x + dx[i];
            int ny = curr.y + dy[i];

            if (!(1 <= nx && nx <= M && 1 <= ny && ny <= N))
            {
                continue;
            }
            if (tempGrid[ny][nx] == 0)
            {
                XY next;
                next.x = nx;
                next.y = ny;
                Virous.push(next);
                tempGrid[ny][nx] = 2;
            }
        }
    }

    int c = Check(tempGrid);
    if (Max < c)
    {
        Max = c;
    }
}

//벽 세우고 BFS 호출
void Wall(int n)
{
    if (n == 3)
    {
        BFS();
        return;
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            if (Grid[i][j] == 0)
            {
                Grid[i][j] = 1;
                Wall(n + 1);
                Grid[i][j] = 0;
            }
        }
    }
}

int main()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= M; j++)
        {
            int input;
            scanf("%d", &input);
            Grid[i][j] = input;

            //초기 바이러스 위치 저장
            if (input == 2)
            {
                XY virousIdx;
                virousIdx.x = j;
                virousIdx.y = i;

                initVirous[initVirousLen++] = virousIdx;
            }
        }
    }
    Wall(0);
    printf("%d", Max);
}