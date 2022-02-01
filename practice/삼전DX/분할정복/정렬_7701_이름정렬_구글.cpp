#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;
int T, N, i, len;
vector<string> s;
string temp;

bool a(string s1, string s2)
{
    if (s1.length() == s2.length())
    {
        return s1 < s2;
    }
    else
    {
        return s1.length() < s2.length();
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    for (int testcase = 1; testcase <= T; ++testcase)
    {
        s.clear();
        cin >> N;
        for (i = 0; i < N; ++i)
        {
            cin >> temp;
            s.push_back(temp);
        }
        //vector에 string을 담고
        //정의된 정렬 방식에 의해 이들을 정렬함
        sort(s.begin(), s.end(), a);
        //unique함수를 통해 중복되는 것들 제거
        s.erase(unique(s.begin(), s.end()), s.end());
        cout << "#" << testcase << "\n";
        len = s.size();
        for (i = 0; i < len; ++i)
        {
            cout << s[i] << "\n";
        }
    }
}