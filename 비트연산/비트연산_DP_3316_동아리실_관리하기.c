#include <stdio.h>
#include <string.h>

long long dp[10000][16]; // A, B, C, D 경우의 수 2^4 - 1 = 15

int main()
{
    int T;
    char club[10000];
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++)
    {
        scanf("%s", club);

        long long case_cnt = 0;
        memset(dp, 0, sizeof(dp));
        //첫째 날에 대한 dp 작성
        for (int i = 0; i < 16; i++)
        {
            if ((i & 1 << (club[0] - 'A')) != 0 && (i & 1) != 0)
            {
                dp[0][i] = 1;
            }
        }

        for (int day = 1; day < strlen(club); day++)
        {
            int admin = 1 << (club[day] - 'A');

            for (int i = 1; i < 16; i++)
            {
                // 2일차 ~
                // 전날까지의 경우의 수가 0이 아니면
                if (dp[day - 1][i] != 0)
                {
                    for (int j = 1; j < 16; j++)
                    {
                        // 전날 나온 사람이 오늘도 나오고 (i & j != 0)
                        // 오늘 나온 사람이 관리자인 경우 count (j & admin != 0)
                        if ((i & j) != 0 && (j & admin) != 0)
                        {
                            dp[day][j] += dp[day - 1][i];
                            dp[day][j] %= 1000000007;
                        }
                    }
                }
            }
        }
        for (int i = 1; i < 16; i++)
        {
            case_cnt += dp[strlen(club) - 1][i];
            case_cnt %= 1000000007;
        }
        printf("#%d %llu\n", tc, case_cnt);
    }
}
