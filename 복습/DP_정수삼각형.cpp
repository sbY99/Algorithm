#include <iostream>
#include <algorithm>

using namespace std;

int N;
int arr[501][501];
int result[501][501];

int main()
{
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            cin >> arr[i][j];
        }
    }

    result[0][0] = arr[0][0];

    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < i + 1; j++)
        {
            if (j == 0)
            {
                result[i][0] = result[i - 1][0] + arr[i][0];
            }
            else if (j == i)
            {
                result[i][i] = result[i - 1][i - 1] + arr[i][i];
            }
            else
            {
                result[i][j] = arr[i][j] + max(result[i - 1][j - 1], result[i - 1][j]);
            }
        }
    }

    int Max = 0;

    for (int i = 0; i < N; i++)
    {
        Max = max(result[N - 1][i], Max);
    }
    cout << Max;

    return 0;
}