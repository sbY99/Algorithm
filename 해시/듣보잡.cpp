#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
using namespace std;



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    map<string, int> m;
    vector<string> vt;
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N + M; i++)
    {
        string str;
        cin >> str;
        m[str]++;
        if (m[str] > 1)
            vt.push_back(str);
    }
    sort(vt.begin(), vt.end());
    cout << vt.size() << '\n';
    for (int i = 0; i < vt.size(); i++)
    {
        cout << vt[i] << '\n';
    }
}