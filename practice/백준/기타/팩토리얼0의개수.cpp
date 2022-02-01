#include <iostream>

using namespace std;

int Count;

int main()
{
    int ftr = 1;
    int N;
    scanf("%d", &N);
    for (int i = 2; i <= N; i++)
    {
        ftr *= i;
        if (ftr % 1000 == 0)
        {
            Count += 3;
            ftr /= 1000;
        }
        else if (ftr % 100 == 0)
        {
            Count += 2;
            ftr /= 100;
        }
        else if (ftr % 10 == 0)
        {
            Count++;
            ftr /= 10;
        }
        ftr %= 100000;
    }
    printf("%d", Count);
    return 0;
}