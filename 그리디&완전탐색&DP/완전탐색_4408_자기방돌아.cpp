#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int room[401];
int N;
int depart, arrival;
int Min, Max;
int Result;

int main(int argc, char **argv)
{
    int test_case;
    int T;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        memset(room, 0, sizeof(room));
        Result = 0;
        cin >> N;
        for (int i = 0; i < N; i++)
        {
            cin >> depart >> arrival;
            Min = min(depart, arrival);
            Max = max(depart, arrival);
            //max가 홀 인 경우
            if ((Max & 1))
            {
                //큰 값을 증가시켜줌
                Max++;
            }
            //min이 짝 인 경우
            if (!(Min & 1))
            {
                //작은 값을 감소시켜줌
                Min--;
            }
            for (int j = Min; j <= Max; j++)
            {
                room[j]++;
            }
        }
        for (int k = 1; k <= 400; k++)
        {
            if (room[k] > Result)
            {
                Result = room[k];
            }
        }
        cout << '#' << test_case << " " << Result << endl;
    }
    return 0;
}