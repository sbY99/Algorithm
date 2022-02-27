#include <iostream>

using namespace std;

long long S;
long long Count;

int main()
{
    cin >> S;
    long long temp = 1;
    while (1)
    {
        S -= temp;
        if (S < 0)
            break;
        Count++;
        temp++;
    }

    printf("%lld", Count);
    return 0;
}