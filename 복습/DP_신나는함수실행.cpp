#include <iostream>

using namespace std;

// -50 ~ 50
int arr[101][101][101];

int main()
{

    // idx: 0 ~ 50 == -50 ~ 0
    // idx: 51 ~ 70 == 1 ~ 20
    // idx: 71 ~ 100 == 21 ~ 50

    for (int i = 0; i <= 70; i++)
    {
        for (int j = 0; j <= 70; j++)
        {
            for (int k = 0; k <= 70; k++)
            {
                if (i <= 50 || j <= 50 || k <= 50)
                {
                    arr[i][j][k] = 1;
                }
            }
        }
    }

    for (int i = 51; i <= 70; i++)
    {
        for (int j = 51; j <= 70; j++)
        {
            for (int k = 51; k <= 70; k++)
            {
                if (i < j && j < k)
                {
                    arr[i][j][k] = arr[i][j][k - 1] + arr[i][j - 1][k - 1] - arr[i][j - 1][k];
                }
                else
                {
                    arr[i][j][k] = arr[i - 1][j][k] + arr[i - 1][j - 1][k] + arr[i - 1][j][k - 1] - arr[i - 1][j - 1][k - 1];
                }
            }
        }
    }

    int a, b, c;

    while (true)
    {
        cin >> a >> b >> c;

        if (a == -1 && b == -1 && c == -1)
            break;
        int result = arr[a + 50][b + 50][c + 50];

        if (a > 20 || b > 20 || c > 20)
            result = arr[70][70][70];

        if (a <= 0 || b <= 0 || c <= 0)
            result = 1;

        printf("w(%d, %d, %d) = %d\n", a, b, c, result);
    }

    return 0;
}