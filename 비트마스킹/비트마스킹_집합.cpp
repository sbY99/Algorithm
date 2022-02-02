#include <iostream>
#include <string>

using namespace std;

int main()
{
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    int N;
    int S = 0;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        string input;
        int x;
        cin >> input;
        if (input == "add")
        {
            cin >> x;
            S = S | (1 << x);
            continue;
        }
        if (input == "remove")
        {
            cin >> x;
            S = S & (~(1 << x));
            continue;
        }
        if (input == "check")
        {
            cin >> x;
            if (S & (1 << x))
            {
                printf("1\n");
            }
            else
            {
                printf("0\n");
            }
            continue;
        }
        if (input == "toggle")
        {
            cin >> x;
            if (S & (1 << x))
            {
                S = S & (~(1 << x));
            }
            else
            {
                S = S | (1 << x);
            }
            continue;
        }
        if (input == "all")
        {
            S = 0b111111111111111111110;
            continue;
        }
        if (input == "empty")
        {
            S = 0;
        }
    }
    return 0;
}