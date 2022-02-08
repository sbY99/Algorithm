#include <iostream>

using namespace std;

void findString(string parent, string pattern)
{
    int parentSize = parent.size();
    int patternSize = pattern.size();
    int parentHash = 0, patternHash = 0, power = 1;
    for (int i = 0; i <= parentSize - patternSize; i++)
    {
        //초기 해시값 설정
        if (i == 0)
        {
            for (int j = 0; j < patternSize; j++)
            {
                //패턴 사이즈에 맞게 맨 마지막 문자부터 차례로 곱해가며
                //초기 해쉬 값 생성
                parentHash += parent[patternSize - 1 - j] * power;
                patternHash += pattern[patternSize - 1 - j] * power;

                //가장 큰 power을 저장하기 위함
                //만약 조건문 없애면, 가장 크게 곱한 power*2가 된 채로 반복문 종료됨
                if (j < patternSize - 1)
                    power *= 2;
            }
        }
        else
        {
            //이전 값에서 맨 앞에 해당하는 뺀 값에 2를 곱하고
            //맨 뒤에 새로 오는 값을 더해줌
            parentHash = 2 * (parentHash - parent[i - 1] * power) + parent[patternSize - 1 + i];
        }

        if (parentHash == patternHash)
        {
            bool finded = true;
            for (int j = 0; j < patternSize; j++)
            {
                if (parent[i + j] != pattern[j])
                {
                    finded = false;
                    break;
                }
            }
            if (finded == true)
            {
                printf("%d번 인덱스에서 발견\n", i);
            }
        }
    }
}

int main()
{
    string parent = "ababacabacaabacaaba";
    string pattern = "abacaaba";
    findString(parent, pattern);
    return 0;
}