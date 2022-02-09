#include <iostream>
#include <queue>

using namespace std;

int N;
priority_queue<int> q;

int main()
{
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