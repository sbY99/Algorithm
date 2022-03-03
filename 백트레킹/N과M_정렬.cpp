#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

int N, M;
int arr[9];
int tempArr[9];
bool visited[9];

void dfs(int temp[], int n)
{
    if (n == M)
    {
        for (int i = 0; i < M; i++)
        {
            printf("%d ", temp[i]);
        }
        printf("\n");
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            if (visited[i] == false)
            {
                tempArr[n] = arr[i];
                visited[i] = true;
                dfs(tempArr, n + 1);
                visited[i] = false;
            }
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
    memset(visited, false, sizeof(visited));
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    Solve();

    return 0;
}