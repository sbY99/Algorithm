#include <iostream>

using namespace std;

int N;
int result;
void dfs(int count);

int main()
{
    scanf("%d", &N);
    dfs(0);
    printf("%d", result);
    return 0;
}

int col[16];

//0~level 행까지 검사함
bool check(int level)
{
    for (int i = 0; i < level; i++)
        if (col[i] == col[level] || abs(col[level] - col[i]) == level - i)
            // 대각선이거나 같은 라인
            return false;
    //col[i]가 의미하는 것이 X좌표, i가 의미하는것이 Y좌표이므로
    //차이가 일정하다면 대각선에 있다.
    return true;
}

void dfs(int count)
{
    if (count == N)
    {
        result++;
        return;
    }

    for (int i = 0; i < N; i++)
    {
        // count행 i번째 열에 퀸 존재
        col[count] = i;
        if (check(count))
        {
            dfs(count + 1);
        }
    }
}
