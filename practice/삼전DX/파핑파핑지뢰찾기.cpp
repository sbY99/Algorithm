/*
#include <iostream>
#include <cstring>
#include <queue>

#define Mine -1
#define Uncheck 1
#define Check 2

using namespace std;

struct XY
{
    int x;
    int y;
};

int N;
int Count;
int grid[301][301];

void bfs(int x, int y);

int main(int argc, char **argv)
{
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        memset(grid, 0, sizeof(grid));
        Count = 0;

        cin >> N;
        char input;

        int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
        int dy[] = {1, -1, 1, 0, -1, 1, 0, -1};

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                scanf(" %c", &input);
                if (input == '*')
                {
                    grid[i][j] = Mine;
                    for (int t = 0; t <= 7; t++)
                    {
                        int nx = dx[t] + j;
                        int ny = dy[t] + i;
                        if (!(1 <= nx && nx <= N && 1 <= ny && ny <= N))
                        {
                            continue;
                        }
                        if (grid[ny][nx] == Mine)
                        {
                            continue;
                        }
                        //주변에 마인 있으면 Uncheck로 할당
                        grid[ny][nx] = Uncheck;
                    }
                }
            }
        }

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                //8방향으로 마인 없으면 bfs시작
                if (grid[i][j] == 0)
                {
                    //체크 후 카운트 1 올림
                    Count++;
                    grid[i][j] = Check;
                    //x,y
                    bfs(j, i);
                }
            }
        }
        
        for(int i=1;i<=N;i++){
            for(int j=1;j<=N;j++){
                if(grid[i][j]==Uncheck){
                    Count++;
                }
            }
        }

        printf("#%d %d\n", test_case, Count);
    }
    return 0;
}

void bfs(int x, int y)
{
    queue<struct XY> q;
    q.push({x,y});
    
    while(q.size()){
        auto curr = q.front();
        q.pop();
        
        int dx[] = {0, 0, 1, 1, 1, -1, -1, -1};
        int dy[] = {1, -1, 1, 0, -1, 1, 0, -1};
        
        for (int i = 0; i <= 7; i++)
        {
            int nx = dx[i] + curr.x;
            int ny = dy[i] + curr.y;
            if (!(1 <= nx && nx <= N && 1 <= ny && ny <= N))
            {
                continue;
            }
            //체크되지 않은, 즉 주변에 마인은 있지만
            //0을 눌렀을 때 숫자가 열리는
            if (grid[ny][nx] == Uncheck)
            {
                //push는 안하고 값 만 변경
                grid[ny][nx]=Check;
                continue;
            }
            //주변에 마인 없으면 체크 후 푸쉬
            if(grid[ny][nx] == 0){
                grid[ny][nx]=Check;
                q.push({nx,ny});
            }
        }
    }
}
*/