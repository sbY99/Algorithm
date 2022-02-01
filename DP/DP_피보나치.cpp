#include <iostream>

using namespace std;

int Num[2][41];

void fibo();

int main()
{
    int T, N;
    Num[0][0] = 1, Num[1][1] = 1;

    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        fibo();
        scanf("%d", &N);
        printf("%d %d", Num[0][N], Num[1][N]);
        printf("\n");
    }

    return 0;
}

void fibo()
{
    for (int i = 2; i <= 40; i++)
    {
        Num[0][i] = Num[0][i - 1] + Num[0][i - 2];
        Num[1][i] = Num[1][i - 1] + Num[1][i - 2];
    }
}