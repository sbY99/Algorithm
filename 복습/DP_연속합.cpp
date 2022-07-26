#include <iostream>
#include <math.h>

using namespace std;

int arr[100001];

int main()
{
    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }

    int sum = 0;
    int MAX = -100000000;

    for (int i = 0; i < N; i++)
    {
        sum = max(arr[i], sum + arr[i]);
        if (MAX < sum)
            MAX = sum;
    }
    cout << MAX;

    return 0;
}