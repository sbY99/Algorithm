#include <iostream>

using namespace std;

int arr[11];
int Count;

int main()
{
    int N, K;
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &arr[i]);
    }

    int idx = N;
    while (1)
    {
        if (K >= arr[idx])
        {
            Count++;
            K -= arr[idx];
        }
        else
        {
            idx--;
        }

        if (K == 0)
        {
            break;
        }
    }
    printf("%d", Count);
    return 0;
}