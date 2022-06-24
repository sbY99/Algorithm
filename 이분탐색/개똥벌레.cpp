#include <iostream>
#include <algorithm>

using namespace std;

int N, H;
int bot[100001];
int top[100001];

void init();
void input();
int crash_bot(int num);
int crash_top(int num);
void solve();

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> N >> H;

    for (int i = 0; i < N / 2; i++)
    {
        cin >> bot[i];
        cin >> top[i];
    }
}

int crash_bot(int num)
{
    int left = 0;
    int right = (N / 2) - 1;
    int mid;

    while (left <= right)
    {
        mid = (left + right) / 2;

        if (bot[mid] < num)
            left = mid + 1;

        else
            right = mid - 1;
    }
    return N / 2 - left;
}

int crash_top(int num)
{
    int left = 0;
    int right = N / 2 - 1;
    int mid;

    while (left <= right)
    {
        mid = (left + right) / 2;

        if (top[mid] < num)
            left = mid + 1;

        else
            right = mid - 1;
    }

    return N / 2 - left;
}

void solve()
{
    sort(bot, bot + N / 2);
    sort(top, top + N / 2);

    int cnt = 0;
    int Min = N + 1;

    for (int h = 1; h <= H; h++)
    {
        int num = crash_bot(h) + crash_top(H - h + 1);

        if (num < Min)
        {
            cnt = 1;
            Min = num;
        }
        else if (num == Min)
        {
            cnt++;
        }
    }
    cout << Min << " " << cnt;
}

int main()
{
    init();
    input();
    solve();
    return 0;
}