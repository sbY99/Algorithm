#include <iostream>
#include <vector>

using namespace std;

vector<int> getPi(string parent)
{
    int parentSize = (int)parent.size();
    int j = 0;

    //parentSize만큼, 0으로 초기화
    vector<int> pi(parentSize, 0);

    //parentSize-1까지 반복하여 테이블 채우면 종료
    for (int i = 1; i < parentSize; i++)
    {
        while (j > 0 && parent[i] != parent[j])
        {
            //비교 대상 인덱스를 pi[j-1]로 옮김
            j = pi[j - 1];
        }
        if (parent[i] == parent[j])
        {
            pi[i] = ++j;
        }
    }
    return pi;
}

void kmp(string parent, string pattern)
{
    vector<int> pi = getPi(pattern);
    int parentSize = (int)parent.size();
    int patternSize = (int)pattern.size();
    int j = 0;

    for (int i = 0; i < parentSize; i++)
    {
        while (j > 0 && parent[i] != pattern[j])
        {
            j = pi[j - 1];
        }
        if (parent[i] == pattern[j])
        {
            //전부 찾은 경우
            if (j == patternSize - 1)
            {
                printf("%d번째에서 찾았습니다.\n", i - patternSize + 2);
                j = pi[j];
            }
            //아직 다 안찾고 단순히 문자 하나가 일치한 경우
            else
            {
                j++;
            }
        }
    }
}

int main()
{
    string parent = "ababacabacaabacaaba";
    string pattern = "abacaaba";
    kmp(parent, pattern);
    return 0;
}