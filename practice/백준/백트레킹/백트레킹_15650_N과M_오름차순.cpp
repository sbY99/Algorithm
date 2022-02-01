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
int check;

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
        if (!printed[i] && check < (1 << (i - 1)))
        {
            printed[i] = true;
            check = check | (1 << (i - 1));
            arr[cnt] = i;
            dfs(cnt + 1);
            printed[i] = false;
            check = check & !(1 << (i - 1));
        }
    }
}