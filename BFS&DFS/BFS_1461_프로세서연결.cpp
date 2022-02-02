
#include <iostream>

using namespace std;

int N;
int Count;
int grid[13][13];

void dfs();

int main(int argc, char **argv)
{
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
        Count = 0;
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                cin >> grid[i][j];
            }
        }
        dfs();
        printf("#%d %d\n", test_case, Count);
    }
    return 0;
}

void dfs()
{
}