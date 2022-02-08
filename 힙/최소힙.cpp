#include <iostream>
#include <queue>

using namespace std;

priority_queue<int, vector<int>, greater<int> > Minheap;

int main()
{
    int N, num;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &num);
        if (num == 0)
        {
            if (Minheap.size() == 0)
            {
                printf("0\n");
            }
            else
            {
                int temp = Minheap.top();
                Minheap.pop();
                printf("%d\n", temp);
            }
        }
        else
        {
            Minheap.push(num);
        }
    }
    return 0;
}