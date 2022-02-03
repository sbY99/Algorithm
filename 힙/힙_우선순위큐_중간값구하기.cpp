#include <iostream>
#include <queue>

using namespace std;

int N;
int result;

int main(int argc, char **argv)
{
    int test_case;
    int T, input1, input2;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        result = 0;
        //내림차순 우선순위큐
        priority_queue<int> Maxheap;
        //오름차순 우선순위큐
        priority_queue<int, vector<int>, greater<int> > Minheap;

        cin >> N >> input1;
        Maxheap.push(input1);

        //maxheap과 minheap의 크기가 같으면 maxheap,
        //maxheap이 더 크면 minheap에 넣음
        for (int i = 0; i < N; i++)
        {
            cin >> input1 >> input2;
            Minheap.push(input1);
            Maxheap.push(input2);

            //만약 top 비교에서 maxheap이 더 크면 교환함으로써
            //minheap이 maxheap보다 무조건 크게 만들음
            //중간 값은 maxheap.top이 됨.
            if (Maxheap.top() > Minheap.top())
            {
                int maxtop = Maxheap.top();
                int mintop = Minheap.top();
                Maxheap.pop();
                Minheap.pop();
                Maxheap.push(mintop);
                Minheap.push(maxtop);
            }

            result += Maxheap.top();
            result %= 20171109;
        }
        printf("#%d %d\n", test_case, result);
    }
    return 0;
}
