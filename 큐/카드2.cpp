#include <iostream>
#include <queue>

using namespace std;

int N;
queue<int> q;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);

    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        q.push(i);
    }

    while (q.size() > 1)
    {
        q.pop();
        int top = q.front();
        q.push(top);
        q.pop();
    }

    cout << q.back();

    return 0;
}