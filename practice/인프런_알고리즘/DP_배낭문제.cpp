#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int N, K;
int Weight[1001];
int Price[1001];

//보석의 최대 개수, 배낭의 최대 무게
//0행, 0열은 전부 0으로 채워짐
int DP[1001][10001];

int main()
{
    //개수, 무개
    cin >> N >> K;
    for (int i = 1; i <= N; i++)
    {
        cin >> Weight[i] >> Price[i];
    }

    //행(i)는 보석의 개수(새로운 보석)
    //열(j)는 배낭의 무게를 의미
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= K; j++)
        {
            //j가 새로운 보석의 무게보다 작으면
            //새로운 보석을 어차피 추가할 수 없기 때문에
            //이전 값을 참고함
            if (j < Weight[i])
            {
                DP[i][j] = DP[i - 1][j];
            }
            //새로운 보석을 배낭에 추가할 수 있다면
            //값 비교 실행
            else
            {
                DP[i][j] = max(DP[i - 1][j], DP[i - 1][j - Weight[i]] + Price[i]);
            }
        }
    }
    cout << DP[N][K];
}