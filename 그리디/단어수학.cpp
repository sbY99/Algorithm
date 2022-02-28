#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

struct Alphabet
{
    int num;
    int Priority;
};

int N;

Alphabet Alpha[27];
string S[11];
int inputNum[11];
int alphaValue[27];

bool cmp(Alphabet a, Alphabet b)
{
    if (a.Priority > b.Priority)
    {
        return true;
    }

    return false;
}

void init()
{
    for (int i = 0; i < 27; i++)
    {
        Alpha[i].num = i;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    init();
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string s;
        cin >> s;
        S[i] = s;

        for (int j = 0; j < s.length(); j++)
        {
            int n = s.length() - j;
            int value = pow(10, n);
            int idx = s[j] - 'A';
            Alpha[idx].Priority += value;
        }
    }

    sort(Alpha, Alpha + 27, cmp);

    int tempNum = 9;

    for (int i = 0; i < 27; i++)
    {
        alphaValue[Alpha[i].num] = tempNum--;
    }

    int Sum = 0;

    for (int i = 0; i < N; i++)
    {
        int len = S[i].length();
        for (int j = 0; j < len; j++)
        {
            inputNum[i] = inputNum[i] * 10 + alphaValue[S[i][j] - 'A'];
        }
        Sum += inputNum[i];
    }
    printf("%d", Sum);
    return 0;
}