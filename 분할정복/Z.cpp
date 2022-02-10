#include <iostream>

using namespace std;
#define MAX 32768 + 1

int N, R, C;
int result;

void divide(int n, int r, int c)
{
    if (n == 1)
    {
        if (r == 0 && c == 0)
            result += 0;
        else if (r == 0 && c == 1)
            result += 1;
        else if (r == 1 && c == 0)
            result += 2;
        else
            result += 3;
        return;
    }
    else
    {
        int temp = (1 << (n - 1));
        if (r < temp && c < temp)
        {
            result += 0;
        }
        else if (r < temp && c >= temp)
        {
            result += temp * temp;
        }
        else if (r >= temp && c < temp)
        {
            result += temp * temp * 2;
        }
        else
        {
            result += temp * temp * 3;
        }
        divide(n - 1, r % temp, c % temp);
    }
}

int main()
{
    //행,열
    // R,C는 0행 0열부터 시작
    cin >> N >> R >> C;
    divide(N, R, C);
    printf("%d", result);
    return 0;
}