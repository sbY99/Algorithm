#include <iostream>

using namespace std;

typedef long long ll;

ll arr[101];

int main()
{
    arr[1] = 1;
    arr[2] = 1;
    arr[3] = 1;
    arr[4] = 2;
    arr[5] = 2;

    for (int i = 6; i <= 100; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 5];
    }

    int T, N;
    cin >> T;

    for (int i = 0; i < T; i++)
    {
        cin >> N;
        cout << arr[N] << "\n";
    }

    return 0;
}