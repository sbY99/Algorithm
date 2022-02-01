#include <iostream>

using namespace std;

int N, M;

void dfs(int cnt);

int main()
{
    cin >> N >> M;
    dfs(0);
}

int arr[9];
bool printed[9] = {false};

void dfs(int cnt)
{
    if (cnt == M)
    {
        for (int i = 0; i < M; i++)
        {
            cout << arr[i] << ' ';
        }
        cout << '\n';
        return;
    }
    for (int i = 1; i <= N; i++)
    {

        arr[cnt] = i;
        dfs(cnt + 1);
    }
}