#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int arr[9];
int tempArr[9];
int visitCheck;

void dfs(int temp[], int n)
{
    if (n == M)
    {
        for (int i = 0; i < M; i++)
        {
            printf("%d ", tempArr[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < N; i++)
        {

            if (visitCheck > arr[i])
            {
                continue;
            }
            tempArr[n] = arr[i];
            int temp = visitCheck;
            visitCheck = arr[i];
            dfs(tempArr, n + 1);
            visitCheck = temp;
        }
    }
}

void Solve()
{
    sort(arr, arr + N);
    dfs(tempArr, 0);
}

int main()
{
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    Solve();
    return 0;
}