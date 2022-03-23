#include <iostream>
#include <cstring>

using namespace std;

int arr[3][100001];
int T;
int N;

void init()
{
    memset(arr, 0, sizeof(arr));
}

void input()
{
    cin >> N;
    for (int j = 1; j <= 2; j++)
    {
        for (int k = 1; k <= N; k++)
        {
            scanf("%d", arr[j][k]);
        }
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        init();
        input();
    }

    return 0;
}