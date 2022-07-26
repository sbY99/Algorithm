#include <iostream>

using namespace std;

int arr[41];

int main()
{
    int n;
    int cnt = 0;
    cin >> n;

    arr[1] = 1;
    arr[2] = 1;

    for (int i = 3; i <= n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
        cnt++;
    }

    cout << arr[n] << " " << cnt;

    return 0;
}