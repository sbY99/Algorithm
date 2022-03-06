#include <iostream>
#include <algorithm>

using namespace std;

int N, M;
int arr[9];
int tempArr[9];
bool visitCheck[9] = {false};

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
        // 마지막 항과, 새로 들어올 값이 같은지 체크
        // 오름차순으로 정렬되었기 때문에 가능
        int check = 0;
        for (int i = 0; i < N; i++)
        {
            int curr = arr[i];
            if (!visitCheck[i] && curr != check)
            {
                tempArr[n] = curr;
                check = tempArr[n];
                visitCheck[i] = true;
                dfs(tempArr, n + 1);
                visitCheck[i] = false;
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
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &arr[i]);
    }
    Solve();

    return 0;
}