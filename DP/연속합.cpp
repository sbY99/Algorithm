#include <iostream>
#include <algorithm>

using namespace std;

int Max;
int arr[100001];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    Max = arr[0];
    int curr = arr[0];

    for (int i = 1; i < n; i++)
    {
        // 0보다 크면, 무조건 포함시키는게 이득임
        if (arr[i] > 0)
        {
            curr += arr[i];
        }
        else
        {
            //이전꺼 까지 포함해서 이득이 되는 경우
            if (curr + arr[i] > 0)
            {
                curr += arr[i];
            }
            // 이전꺼 까지 포함해서 손해가 되는 경우
            // 초기화 해줌
            else
            {
                // Max값이 음수 인데
                //더 작은 음수가 나온 경우
                if (Max < arr[i])
                {
                    Max = arr[i];
                }
                curr = 0;
                continue;
            }
        }
        if (Max < curr)
        {
            Max = curr;
        }
    }
    printf("%d", Max);
    return 0;
}