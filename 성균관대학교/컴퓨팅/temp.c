#include <stdio.h>
#include <string.h>
#define swap(x, y) \
    {                    \
        int temp = x;      \
        x = y;           \
        y = temp;           \
    }

int result, len;
int arr[6];
int visit[1000000][11];

void convert(int number);
int toNum(int arr[]);
void dfs(int arr[], int count);

int main()
{
    int test_case;
    int T;
    int number, count;
    scanf("%d", &T);
    getchar();
    for (test_case = 1; test_case <= T; ++test_case)
    {
        result=0;
        len=0;
        memset(visit, 0, sizeof(visit));

        scanf("%d %d", &number, &count);
        getchar();
        convert(number);
        dfs(arr, count);
        printf("#%d %d\n", test_case, result);
    }
    return 0; //정상종료시 반드시 0을 리턴해야합니다.
}

void convert(int number)
{
    int num = number;
    while (num)
    {
        num /= 10;
        len++;
    }
    for (int i = len - 1; i >= 0; i--)
    {
        arr[i] = number % 10;
        number /= 10;
    }
}

int toNum(int tmp[])
{
    int temp = 0;
    for (int i = 0; i < len; i++)
    {
        temp = temp * 10 + tmp[i];
    }
    return temp;
}

void dfs(int tmp[], int count)
{
    if (count == 0)
    {
        int temp = toNum(tmp);
        if (temp > result)
        {
            result = temp;
            return;
        }
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            swap(tmp[i], tmp[j]);
            if (visit[toNum(tmp)][count] == 0)
            {
                visit[toNum(tmp)][count] = 1;
                dfs(tmp, count - 1);
            }
            swap(tmp[i], tmp[j]);
        }
    }
}
