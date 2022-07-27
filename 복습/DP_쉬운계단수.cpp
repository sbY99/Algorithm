#include <iostream>

using namespace std;

typedef long long ll;

ll arr[10][101];

int main()
{
    int N;

    cin >> N;

    for (int i = 1; i <= 9; i++)
    {
        arr[i][1] = 1;
    }

    for (int i = 2; i <= N; i++)
    {
        arr[0][i] = arr[1][i - 1];
        arr[9][i] = arr[8][i - 1];

        for (int j = 1; j <= 8; j++)
        {
            arr[j][i] = (arr[j - 1][i - 1] + arr[j + 1][i - 1]) % 1000000000;
        }
    }

    ll sum = 0;

    for (int i = 0; i <= 9; i++)
    {
        sum += arr[i][N];
    }
    cout << sum % 1000000000;

    return 0;
}