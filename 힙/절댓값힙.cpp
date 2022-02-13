#include <iostream>
#include <cmath>
#include <queue>

using namespace std;

struct cmp
{
    bool operator()(int n1, int n2)
    {
        if (abs(n1) > abs(n2))
        {
            return true;
        }
        else if (abs(n1) == abs(n2))
        {
            if (n1 > n2)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
};

priority_queue<int, vector<int>, cmp> q;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int input;
        scanf("%d", &input);
        if (input == 0)
        {
            if (q.size() == 0)
            {
                printf("0\n");
            }
            else
            {
                printf("%d\n", q.top());
                q.pop();
            }
        }
        else
        {
            q.push(input);
        }
    }

    return 0;
}