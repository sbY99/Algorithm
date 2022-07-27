#include <iostream>
#include <math.h>

using namespace std;

int N;
int value[10001];
int arr[3][10001];

int main()
{
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> value[i];
    }

    arr[0][0] = 0;
    arr[1][0] = value[0];
    arr[2][0] = 0;

    for (int i = 1; i < N; i++)
    {
        arr[0][i] = max(arr[0][i - 1], max(arr[1][i - 1], arr[2][i - 1]));
        arr[1][i] = arr[0][i - 1] + value[i];
        arr[2][i] = arr[1][i - 1] + value[i];
    }

    int Max = 0;
    for (int i = 0; i < 3; i++)
    {
        Max = max(arr[i][N - 1], Max);
    }
    cout << Max;

    return 0;
}