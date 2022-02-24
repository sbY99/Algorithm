#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> loop;
int Result;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int input;
        scanf("%d", &input);
        loop.push_back(input);
    }
    sort(loop.begin(), loop.end());

    int temp = N;
    for (int i = 0; i < N; i++)
    {
        if (loop[i] * temp > Result)
        {
            Result = loop[i] * temp;
        }
        temp--;
    }

    printf("%d", Result);

    return 0;
}