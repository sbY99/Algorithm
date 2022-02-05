
#include <iostream>
#include <queue>

using namespace std;

priority_queue<int> Maxheap;
priority_queue<int, vector<int>, greater<int> > Minheap;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int input;
        scanf("%d", &input);

        if (Maxheap.size() == Minheap.size())
        {
            Maxheap.push(input);
        }
        else if (Maxheap.size() > Minheap.size())
        {
            Minheap.push(input);
        }
        //Minheap에 값이 없는 경우 top을 호출하면 에러 발생
        if (Minheap.size() == 0)
        {
            printf("%d\n", Maxheap.top());
            continue;
        }
        //일반 큐의 경우 .front()
        if (Maxheap.top() > Minheap.top())
        {
            int maxheap = Maxheap.top();
            int minheap = Minheap.top();
            Maxheap.pop();
            Minheap.pop();
            Maxheap.push(minheap);
            Minheap.push(maxheap);
        }
        printf("%d\n", Maxheap.top());
    }
    return 0;
}
