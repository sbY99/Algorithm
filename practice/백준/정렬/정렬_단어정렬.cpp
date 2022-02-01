#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

vector<string> Vec;
string input;

bool cmp(string s1, string s2)
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
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> input;
        Vec.push_back(input);
    }
    sort(Vec.begin(), Vec.end(), cmp);
    //unique함수를 통해 중복되는 것들 제거
    Vec.erase(unique(Vec.begin(), Vec.end()), Vec.end());
    N = Vec.size();
    for (int i = 0; i < N; i++)
    {
        cout << Vec[i] << '\n';
    }
}