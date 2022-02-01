#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
    int N, M;
    while (1)
    {
        scanf("%d %d", &N, &M);
        if (!(N | M))
        {
            break;
        }
        if (N > M)
        {
            //N이 크면 N이 M의 배수인지 검사
            if (N % M == 0)
            {
                printf("multiple\n");
            }
            else
            {
                printf("neither\n");
            }
        }
        else
        {
            if (M % N == 0)
            {
                printf("factor\n");
            }
            else
            {
                printf("neither\n");
            }
        }
    }
    return 0;
}