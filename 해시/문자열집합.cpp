#include <iostream>
#include <string>
#include <set>

using namespace std;

int n, m, cnt = 0;
set<string> s;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        string tmp;
        cin >> tmp;
        s.insert(tmp);
    }

    for (int i = 0; i < m; i++)
    {
        string tmp;
        cin >> tmp;
        if (s.find(tmp) != s.end())
            cnt++;
    }

    cout << cnt;
}