#include <iostream>
#include <algorithm>

using namespace std;

int N;

int grid[510][510];

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            int input;
            scanf("%d", &input);
            grid[i][j] = max(grid[i - 1][j - 1], grid[i - 1][j]) + input;
        }
    }

    int max = 0;

    for (int i = 1; i <= N; i++)
    {
        if (max < grid[N][i])
        {
            max = grid[N][i];
        }
    }

    printf("%d", max);

    return 0;
}