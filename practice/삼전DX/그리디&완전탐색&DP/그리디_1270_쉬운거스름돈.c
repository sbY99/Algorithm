
#include <stdio.h>

void func(int money);

int main()
{
    int test_case;
    int T, money;
    scanf("%d", &T);
    getchar();
    for (test_case = 1; test_case <= T; ++test_case)
    {
        scanf("%d", &money);
        getchar();
        printf("#%d\n", test_case);
        func(money);
    }
    return 0;
}

void func(int money)
{
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0, h = 0;
    if (money >= 50000)
    {
        a = money / 50000;
        money -= 50000 * a;
    }
    if (money >= 10000)
    {
        b = money / 10000;
        money -= 10000 * b;
    }
    if (money >= 5000)
    {
        c = money / 5000;
        money -= 5000 * c;
    }
    if (money >= 1000)
    {
        d = money / 1000;
        money -= 1000 * d;
    }
    if (money >= 500)
    {
        e = money / 500;
        money -= 500 * e;
    }
    if (money >= 100)
    {
        f = money / 100;
        money -= 100 * f;
    }
    if (money >= 50)
    {
        g = money / 50;
        money -= 50 * g;
    }
    if (money >= 10)
    {
        h = money / 10;
        money -= 10 * h;
    }
    printf("%d %d %d %d %d %d %d %d", a, b, c, d, e, f, g, h);
    printf("\n");
}