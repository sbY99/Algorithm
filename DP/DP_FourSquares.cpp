#include <iostream>
#include <math.h>

using namespace std;

int List[50001];
int breakpoint[50001];
int idx;

bool isSquare(unsigned int num);
int func(int num);

int main()
{
    int N;
    cin >> N;

    List[1] = 1;
    breakpoint[++idx] = 1;

    for (int i = 2; i <= N; i++)
    {
        if (isSquare(i))
        {
            List[i] = 1;
            breakpoint[++idx] = i;
            continue;
        }
        List[i] = func(i);
    }
    printf("%d", List[N]);
    return 0;
}

bool isSquare(unsigned int num)
{
    unsigned int temp = (unsigned int)(sqrt((double)num) + 0.5);
    return temp * temp == num;
}

int func(int num)
{
    //breakpoint 배열의 맨 뒤
    int temp_idx = idx;
    int result = 4;

    while (1)
    {
        if (temp_idx == 0)
        {
            return result;
        }
        if (List[num - breakpoint[temp_idx]] + 1 < result)
        {
            result = List[num - breakpoint[temp_idx]] + 1;
        }
        temp_idx--;
    }
}