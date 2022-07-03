#include <iostream>
#include <deque>
#include <vector>

using namespace std;

int N, M, cnt;
vector<int> targets;
deque<int> dq;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);

    cin >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        dq.push_back(i);
    }

    for (int i = 0; i < M; i++)
    {
        int target;
        cin >> target;
        targets.push_back(target);
    }

    for (int i = 0; i < M; i++)
    {
        int target = targets[i];

        deque<int> temp_dq1(dq);
        deque<int> temp_dq2(dq);
        int left_cnt = 0;
        int right_cnt = 0;

        if (dq.front() == target)
        {
            dq.pop_front();
            continue;
        }

        while (temp_dq1.front() != target)
        {
            left_cnt++;
            int temp_top = temp_dq1.front();
            temp_dq1.pop_front();
            temp_dq1.push_back(temp_top);
        }

        while (temp_dq2.front() != target)
        {
            right_cnt++;
            int temp_top = temp_dq2.back();
            temp_dq2.pop_back();
            temp_dq2.push_front(temp_top);
        }

        if (left_cnt < right_cnt)
        {
            cnt += left_cnt;
            dq = temp_dq1;
            dq.pop_front();
        }
        else
        {
            cnt += right_cnt;
            dq = temp_dq2;
            dq.pop_front();
        }
    }

    cout << cnt;

    return 0;
}