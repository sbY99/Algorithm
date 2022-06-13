#include <iostream>
#include <set>

using namespace std;

int N, M;
set<int> s;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int cnt = 0;

    cin >> N >> M;

    for (int i = 0; i < N; i++)
    {
        int tmp;
        cin >> tmp;
        s.insert(tmp);
    }

    for (int i = 0; i < M; i++)
    {
        int tmp;
        cin >> tmp;
        if (s.find(tmp) != s.end())
            cnt++;
    }

    cout << N + M - 2 * cnt;

    return 0;
}