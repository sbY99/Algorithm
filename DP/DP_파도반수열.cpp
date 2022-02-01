#include <iostream>

using namespace std;

long long arr[101];
void f();

int main()
{
    int T, N;
    f();
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        cin >> N;
        printf("%lld\n", arr[N]);
    }

    return 0;
}

void f()
{
    arr[1] = 1;
    arr[2] = 1;
    arr[3] = 1;
    arr[4] = 2;
    arr[5] = 2;
    arr[6] = 3;
    arr[7] = 4;
    arr[8] = 5;
    arr[9] = 7;
    arr[10] = 9;
    for (int i = 11; i <= 101; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 5];
    }
}