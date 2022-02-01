#include <iostream>

using namespace std;

int result;

void W();

int H[21][21][21];

int main()
{
    int a, b, c;
    W();
    while (1)
    {
        cin >> a >> b >> c;
        if (a == -1 && b == -1 && c == -1)
        {
            break;
        }
        if (a <= 0 || b <= 0 || c <= 0)
        {
            printf("w(%d, %d, %d) = %d\n", a, b, c, 1);
            continue;
        }
        if (a > 20 || b > 20 || c > 20)
        {
            printf("w(%d, %d, %d) = %d\n", a, b, c, H[20][20][20]);
            continue;
        }
        printf("w(%d, %d, %d) = %d\n", a, b, c, H[a][b][c]);
    }
    return 0;
}

void W()
{
    H[0][0][0] = 1;
    for (int i = 0; i <= 20; i++)
    {
        for (int j = 0; j <= 20; j++)
        {
            H[0][i][j] = 1;
            H[i][0][j] = 1;
            H[i][j][0] = 1;
        }
    }

    for (int a = 1; a <= 20; a++)
    {
        for (int b = 1; b <= 20; b++)
        {
            for (int c = 1; c <= 20; c++)
            {
                if (a < b && b < c)
                {
                    H[a][b][c] = H[a][b][c - 1] + H[a][b - 1][c - 1] - H[a][b - 1][c];
                }
                else
                {
                    H[a][b][c] = H[a - 1][b][c] + H[a - 1][b - 1][c] + H[a - 1][b][c - 1] - H[a - 1][b - 1][c - 1];
                }
            }
        }
    }
}