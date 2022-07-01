#include <iostream>
#include <vector>

using namespace std;

int N;
int seq[100001];
vector<int> stack;
vector<char> result;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++)
    {
        cin >> seq[i];
    }

    int num = 1;
    int seq_idx = 0;

    while (num <= N)
    {
        result.push_back('+');

        if (num != seq[seq_idx])
        {
            stack.push_back(num++);
        }
        else
        {
            result.push_back('-');

            seq_idx++;
            num++;
            while (stack.size() > 0 && stack.back() == seq[seq_idx])
            {
                stack.pop_back();
                seq_idx++;

                result.push_back('-');
            }
        }
    }

    if (stack.size() == 0)
    {
        for (int i = 0; i < result.size(); i++)
        {
            cout << result[i] << "\n";
        }
    }
    else
    {
        cout << "NO";
    }

    return 0;
}