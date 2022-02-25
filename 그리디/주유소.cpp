#include <iostream>

using namespace std;
#define Max 100001

long long City[Max];
long long Road[Max];
long long Result;
long long N;

void Solve()
{
    long long temp = 1000000000;

    for (int i = 0; i < N - 1; i++)
    {
        if (City[i] < temp)
        {
            temp = City[i];
        }
        Result += temp * Road[i];
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    for (int i = 0; i < N - 1; i++)
    {
        cin >> Road[i];
    }

    for (int i = 0; i < N; i++)
    {
        cin >> City[i];
    }
    Solve();

    cout << Result;

    return 0;
}