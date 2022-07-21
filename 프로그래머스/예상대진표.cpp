#include <iostream>

using namespace std;

int answer;

bool isEnd(int a, int b);
int next(int num);
int solution(int n, int a, int b);

bool isEnd(int a, int b)
{
    if (a < b)
    {
        // 작은 값은 홀수여야함
        if ((b - a == 1) && (a % 2) == 1)
            return true;
        return false;
    }
    else
    {
        // 작은 값은 홀수여야함
        if ((a - b == 1) && (b % 2) == 1)
            return true;
        return false;
    }
}

int next(int num)
{
    if (num % 2 == 1)
        return (num + 1) / 2;
    else
        return num / 2;
}

int solution(int n, int a, int b)
{
    answer++;

    if (isEnd(a, b))
        return answer;

    return solution(n, next(a), next(b));
}

int main()
{
    int n, a, b;
    cin >> n >> a >> b;

    cout << solution(n, a, b);
    return 0;
}