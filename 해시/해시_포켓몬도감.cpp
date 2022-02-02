
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int N, M;

string name[100001];

map<string, int> m;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        string s;
        cin >> s;
        name[i] = s;

        //pair 객체를 생성하여 insert해줌
        //m[s]=i도 가능
        //m.insert({s,i})도 가능
        m.insert(make_pair(s, i));
    }

    for (int i = 1; i <= M; i++)
    {
        string s;
        int n;
        cin >> s;
        if (isdigit(s[0]) == true)
        {
            n = stoi(s);
            cout << name[n] << '\n';
        }
        else
        {
            cout << m.find(s)->second << '\n';
        }
    }
}