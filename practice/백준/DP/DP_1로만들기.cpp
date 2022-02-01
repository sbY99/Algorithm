#include <iostream>
#include <algorithm>

using namespace std;

int List[1000001];

int main()
{
    int X;
    scanf("%d", &X);
    List[1] = 0, List[2] = 1, List[3] = 1;

    for (int i = 4; i <= X; i++)
    {
        if (i % 3 == 0 && i % 2 == 0)
        {
            List[i] = min(List[i / 3], min(List[i / 2], List[i - 1])) + 1;
        }
        else if (i % 3 == 0)
        {
            List[i] = min(List[i / 3], List[i - 1]) + 1;
        }
        else if (i % 2 == 0)
        {
            List[i] = min(List[i / 2], List[i - 1]) + 1;
        }
        else
        {
            List[i] = List[i - 1] + 1;
        }
    }

    printf("%d", List[X]);
    return 0;
}