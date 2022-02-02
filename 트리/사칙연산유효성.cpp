#include <iostream>

using namespace std;

int N;
int Check;

int main(int argc, char **argv)
{
    int test_case;
    for (test_case = 1; test_case <= 10; ++test_case)
    {
        cin >> N;
        Check = 0;
        for (int i = 1; i <= N; i++)
        {
            int idx, left, right;
            char op;
            cin >> idx >> op;
            if (idx * 2 < N)
            {
                cin >> left >> right;
                //완전이진트리이므로 잎 노드의 경우를 제외하고는 무조건 연산자
                if (!(op == '+' || op == '-' || op == '*' || op == '/'))
                {
                    Check = 1;
                }
            }
            else if (idx * 2 == N)
            {
                cin >> left;
                //완전이진트리이므로 잎 노드의 경우 무조건 숫자
                if ((op == '+' || op == '-' || op == '*' || op == '/'))
                {
                    Check = 1;
                }
            }
        }
        //짝수 노드이면 무조건 연산 불가
        if (N % 2 == 0)
            Check = 1;

        if (Check == 1)
            printf("#%d 0\n", test_case);
        else
            printf("#%d 1\n", test_case);
    }
    return 0;
}
