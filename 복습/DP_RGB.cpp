#include <iostream>
#include <math.h>

using namespace std;

int N;
int R, G, B;
int arr[3][1001];

int main()
{
    cin >> N;
    cin >> arr[0][1] >> arr[1][1] >> arr[2][1];

    for (int i = 2; i <= N; i++)
    {
        cin >> R >> G >> B;

        // R,G,B
        arr[0][i] = R + min(arr[1][i - 1], arr[2][i - 1]);
        arr[1][i] = G + min(arr[0][i - 1], arr[2][i - 1]);
        arr[2][i] = B + min(arr[1][i - 1], arr[0][i - 1]);
    }

    int MIN = 1000000;

    for (int i = 0; i < 3; i++)
    {
        MIN = min(MIN, arr[i][N]);
    }
    cout << MIN;

    return 0;
}