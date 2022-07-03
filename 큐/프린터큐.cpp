#include <iostream>
#include <queue>
#include <string.h>

using namespace std;

int T, N, target;
int imp;
int importance[10];

void init();
void input();
void solve();

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
}

void input()
{
    cin >> T;
}

void solve()
{
    for (int i = 0; i < T; i++)
    {
        memset(importance, 0, sizeof(importance));

        int cnt = 0;
        cin >> N >> target;
        queue<pair<int, int>> q;

        for (int j = 0; j < N; j++)
        {
            cin >> imp;
            // idx, importance
            q.push(make_pair(j, imp));
            importance[imp]++;
        }

        while (q.size())
        {
            bool isPossible = true;

            int top_idx = q.front().first;
            int top_imp = q.front().second;

            for (int j = top_imp + 1; j <= 9; j++)
            {
                if (importance[j] > 0)
                {
                    isPossible = false;
                    break;
                }
            }

            if (isPossible)
            {
                importance[top_imp]--;
                cnt++;

                // Print and Escape the 'while loop'
                if (top_idx == target)
                {
                    cout << cnt << "\n";
                    break;
                }
                else
                {
                    q.pop();
                }
            }
            else
            {
                pair<int, int> p = q.front();
                q.pop();
                q.push(p);
            }
        }
    }
}

int main()
{
    init();
    input();
    solve();
    return 0;
}
