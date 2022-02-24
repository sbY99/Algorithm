#include <iostream>

using namespace std;

int main()
{
    int N;
    cin >> N;
    int Count = 0;
    int Start = 1000;
    Start = Start - N;
    while (Start != 0)
    {
        if (Start >= 500)
        {
            Start -= 500;
            Count++;
        }
        else if (Start >= 100)
        {
            Start -= 100;
            Count++;
        }
        else if (Start >= 50)
        {
            Start -= 50;
            Count++;
        }
        else if (Start >= 10)
        {
            Start -= 10;
            Count++;
        }
        else if (Start >= 5)
        {
            Start -= 5;
            Count++;
        }
        else if (Start >= 1)
        {
            Start -= 1;
            Count++;
        }
    }
    printf("%d", Count);
    return 0;
}