#include <iostream>
#include <algorithm>
using namespace std;

int N;
int grid[30][30];
int cnt = 2;
int ap[1000];

void dfs(int x, int y);

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        //띄어쓰기 없이 한 줄로 입력 받으므로
        char line[30];
        scanf("%s", line);
        for (int j = 0; j < N; j++)
        {
            grid[i][j] = line[j] - '0';
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //배열에 1이 저장되어 있다면
            //아직 단지가 정해지지 않은 아파트이므로
            if (grid[i][j] == 1)
            {
                dfs(i, j);
                cnt++;
            }
        }
    }

    printf("%d\n", cnt - 2);

    //sort의 경우, 시작 인덱스와 마지막인덱스+1을 넣어야함
    //cnt가 5, 즉 3개의 단지가 있다면
    //ap[2] ap[3] ap[4]의 정렬을 위해
    //sort(&ap[2],&ap[5])가 되어야 함
    sort(&ap[2], &ap[cnt]);

    for (int i = 2; i < cnt; i++)
    {
        printf("%d\n", ap[i]);
    }
}

void dfs(int x, int y)
{
    grid[x][y] = cnt;
    ap[cnt]++;

    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        //조건을 여기에 넣는 것이
        //dfs call이 줄어든다는 측면에서 더욱 효율 적임
        if (!(0 <= nx && nx < N && 0 <= ny && ny < N))
        {
            continue;
        }
        if (grid[nx][ny] != 1)
        {
            continue;
        }
        dfs(nx, ny);
    }
}