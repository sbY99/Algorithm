#include <iostream>
#include <vector>

using namespace std;

#define MAX 1000001

int N;
int arr[MAX];
int result[MAX];
vector<int> stack;

void init();
void input();
void solve();
void output();

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
}

void solve()
{
    for (int i = N - 1; i >= 0; i--)
    {
        if (stack.size() == 0)
        {
            result[i] = -1;
            stack.push_back(arr[i]);
        }
        else
        {
            if (arr[i] < stack.back())
            {
                result[i] = stack.back();
                stack.push_back(arr[i]);
            }
            else
            {
                while (stack.size() > 0 && stack.back() <= arr[i])
                {
                    stack.pop_back();
                }

                if (stack.size() == 0)
                {
                    result[i] = -1;
                    stack.push_back(arr[i]);
                }
                else
                {
                    result[i] = stack.back();
                    stack.push_back(arr[i]);
                }
            }
        }
    }
}

void output()
{
    for (int i = 0; i < N; i++)
    {
        cout << result[i] << " ";
    }
}

int main()
{
    init();
    input();
    solve();
    output();

    return 0;
}