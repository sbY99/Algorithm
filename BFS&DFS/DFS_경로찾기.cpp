#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define Max 101

int N;
int Grid[Max][Max];

void dfs(int idx)
{
    vector<int> Stack;
    bool visited[N + 1];
    memset(visited, false, sizeof(visited));
    Stack.push_back(idx);

    while (Stack.size() > 0)
    {
        int curr_idx = Stack.back();
        Stack.pop_back();
        for (int i = 1; i <= N; i++)
        {
            if (Grid[curr_idx][i] == 1 && visited[i] == false)
            {
                visited[i] = true;
                Grid[idx][i] = 1;
                Stack.push_back(i);
            }
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            scanf("%d", &Grid[i][j]);
        }
    }

    for (int i = 1; i <= N; i++)
    {
        dfs(i);
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            printf("%d ", Grid[i][j]);
        }
        printf("\n");
    }
    return 0;
}