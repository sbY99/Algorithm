#include <iostream>
using namespace std;

int N;

void input();
void rec(int i, int j, int num);
void solve();

void input()
{
    cin >> N;
}

void rec(int i, int j, int num)
{
    if ((i / (num / 3)) % 3 == 1 && (j / (num / 3)) % 3 == 1)
    {
        cout << ' ';
    }
    else
    {
        // num < 3
        if (num / 3 == 0)
            cout << '*';
        else
            rec(i, j, num / 3);
    }
}

void solve()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            rec(i, j, N);
        cout << '\n';
    }
}

int main()
{
    input();
    solve();
}