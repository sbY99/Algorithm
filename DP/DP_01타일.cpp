#include <iostream>

using namespace std;

int arr[1000001];

int main()
{
    int N;
    cin >> N;
    arr[1] = 1;
    arr[2] = 2;
    arr[3] = 3;
    for (int i = 4; i <= N; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
        arr[i] %= 15746;
    }
    printf("%d", arr[N]);
    return 0;
}