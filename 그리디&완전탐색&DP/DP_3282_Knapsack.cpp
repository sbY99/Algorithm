#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int N, K;
int Weight[101], Price[101];
int DP[101][1001];

int main()
{
    int test_case;
    int T;
    scanf("%d", &T);
    getchar();

    for (test_case = 1; test_case <= T; ++test_case)
    {
        scanf("%d %d", &N, &K);
        getchar();
        memset(DP, 0, sizeof(DP));

        //1~N까지
        for (int i = 1; i <= N; i++)
        {
            scanf("%d %d", &Weight[i], &Price[i]);
            getchar();
        }

        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= K; j++)
            {
                //가방의 무게보다 새로운 물건의 부피가 더 크면
                //이전 값 대입
                if (Weight[i] > j)
                {
                    DP[i][j] = DP[i - 1][j];
                }
                //새로운 물건을 담을 수 있으면
                //비교 실행
                else
                {
                    DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - Weight[i]] + Price[i]);
                }
            }
        }
        cout << '#' << test_case << " " << DP[N][K] << endl;
    }
    return 0; //정상종료시 반드시 0을 리턴해야합니다.
}