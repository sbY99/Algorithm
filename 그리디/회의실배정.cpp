#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
vector<pair<int, int> > v;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int start, end;
        scanf("%d %d", &start, &end);
        //종료 시간으로 정렬하기 위해 반대로 입력해줌
        v.push_back(make_pair(end, start));
    }
    sort(v.begin(), v.end());

    //가장 빨리 끝나는 회의의 종료 시간
    int time = v[0].first;

    //첫 회의 포함
    int result = 1;

    for (int i = 1; i < v.size(); i++)
    {
        //다음 회의가 가능하면
        if (time <= v[i].second)
        {
            result++;
            time = v[i].first;
        }
    }
    printf("%d", result);
    return 0;
}