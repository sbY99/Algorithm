#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;

char s1[1001];
char s2[1001];
int len1;
int len2;

int DP[1001][1001];

int main()
{
    //1번째 인덱스 부터 문자열을 받음(0번째는 0으로 비워둠)
    cin >> &s1[1] >> &s2[1];
    len1 = strlen(&s1[1]), len2 = strlen(&s2[1]);

    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            //i,j 번째의 문자가 일치할 때
            if (s1[i] == s2[j])
            {
                DP[i][j] = DP[i - 1][j - 1] + 1;
            }
            //다를 경우
            else
            {
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);
            }
        }
    }
    cout << DP[len1][len2];
}