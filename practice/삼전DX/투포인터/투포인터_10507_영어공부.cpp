#include <iostream>

using namespace std;

int arr[200001];
int diff[200001];

int main()
{
    int test_case;
    int T;
    int N, P;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N >> P;
        for (int i = 0; i < N; i++)
        {
            scanf(" %d", &arr[i]);
        }
        //0-1 거리 차: diff 0 인덱스
        //1-2 거리 차: diff 1 인덱스
        //만약 배열 순서가 3,5라면
        //diff = 5-3-1이 됨
        for (int i = 0; i < N - 1; i++)
        {
            diff[i] = arr[i + 1] - arr[i] - 1;
        }

        int start = 0;
        int end = 0;
        int distance = 0;

        int max = -1;
        while (end < N)
        {
            //수를 더 채울 수 있다면
            if (distance <= P)
            {
                //end를 이후 요소로 옮기고
                //거리와, D의 나머지를 갱신함
                distance += diff[end];
                end++;
            }
            //수를 더 채울 수 없다면
            else
            {
                int temp = arr[end - 1] - arr[start] + 1 + P - (distance - diff[end - 1]);
                if (temp > max)
                {
                    max = temp;
                }
                distance -= diff[start];
                start++;
            }
        }
        //반복문 종료 후, 마지막날을 포함했을 때 최대가 되는 경우 판단
        int temp = arr[end - 1] - arr[start] + 1 + P - (distance - diff[end - 1]);

        if (temp > max)
        {
            max = temp;
        }
        printf("#%d %d\n", test_case, max);
    }
    return 0;
}