#include <stdio.h>
#include <math.h>

void hanoi(int n, int from, int tmp, int to);

int main(void)
{
    int n;
    scanf("%d", &n);
    int cnt = pow(2, n) - 1;
    printf("%d\n", cnt);
    hanoi(n, 1, 2, 3);
}

void hanoi(int n, int from, int tmp, int to)
{
    if (n == 1)
    {
        printf("%d %d\n", from, to);
    }
    else
    {
        hanoi(n - 1, from, to, tmp);
        printf("%d %d\n", from, to);
        hanoi(n - 1, tmp, from, to);
    }
}