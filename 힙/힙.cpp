#include <iostream>

#define MAX 100001
using namespace std;

int heap[MAX];
int Cnt;

void Init()
{
    Cnt = 0;
}

void Push(int x)
{
    heap[++Cnt] = x;
    int curr = Cnt;
    while (curr / 2 >= 1)
    {
        int parent = curr / 2;

        //최대 힙이므로 부모가 크면 stop
        if (heap[parent] > heap[curr])
            break;

        int temp = heap[parent];
        heap[parent] = heap[curr];
        heap[curr] = temp;

        curr = parent;
    }
}

void Pop()
{
    if (Cnt < 1)
    {
        printf("-1 ");
        return;
    }

    int m = heap[1];
    int l = heap[Cnt--];
    heap[1] = l;
    int curr = 1;

    //자식이 있으면
    while (curr * 2 <= Cnt)
    {
        int child;
        if (curr * 2 == Cnt)
            child = curr * 2;

        else
            child = heap[curr * 2] > heap[curr * 2 + 1] ? curr * 2 : curr * 2 + 1;

        if (heap[curr] > heap[child])
            break;

        int temp = heap[child];
        heap[child] = heap[curr];
        heap[curr] = temp;
        curr = child;
    }

    printf("%d ", m);
}

int main(int argc, char **argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int test_case;
    int T, N;
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        cin >> N;
        Init();
        printf("#%d ", test_case);
        for (int i = 0; i < N; i++)
        {
            int input;
            cin >> input;
            switch (input)
            {
            case 1:
                int num;
                cin >> num;
                Push(num);
                break;
            case 2:
                Pop();
                break;
            }
        }
        printf("\n");
    }
    return 0;
}