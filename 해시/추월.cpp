#include <iostream>
#include <string>
#include <map>

using namespace std;

int N;
int arr[1001];
map<string, int> m;

int main()
{
    int cnt = 0;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string tmp;
        cin >> tmp;
        m[tmp] = i;
    }

    for (int i = 0; i < N; i++)
    {
        string tmp;
        cin >> tmp;
        int value = m[tmp];

        // 추월 당하면, arr[value]++
        // 즉, 추월 당하면 이전의 순서에서 한단계 밀림
        // 이 상태에서 추월 당했는지 여부 판별
        if (value + arr[value] > i)
        {
            cnt++;
            for (int i = 0; i < value; i++)
            {
                arr[i]++;
            }
        }
    }
    cout << cnt;

    return 0;
}