#include <iostream>
#include <string>
#include <map>
using namespace std;

map<string, string> m;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int N, M;
    cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        string input1;
        string input2;
        cin >> input1 >> input2;
        m.insert(make_pair(input1, input2));
    }

    for (int i = 0; i < M; i++)
    {
        string input;
        cin >> input;
        cout << m.find(input)->second << '\n';
    }

    return 0;
}