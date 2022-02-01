#include <iostream>

using namespace std;

int arr[12];

int main()
{
    int T;
    arr[1] = 1, arr[2] = 2, arr[3] = 4;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int N;
        cin >> N;
        for (int j = 4; j <= N; j++)
        {
            arr[j] = arr[j - 3] + arr[j - 2] + arr[j - 1];
        }
        printf("%d\n", arr[N]);
    }
    return 0;
}