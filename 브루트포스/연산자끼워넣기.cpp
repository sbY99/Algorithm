#include <iostream>
#include <vector>

using namespace std;

int N;
int Min, Max;
vector<int> v;
int checked[4];

void Solve(int num, int r)
{
    if (num == N)
    {
        if (r < Min)
        {
            Min = r;
        }
        if (r > Max)
        {
            Max = r;
        }
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            int temp = r;
            if (checked[i] == 0)
                continue;
            if (i == 0)
            {
                temp += v[num];
                checked[i]--;
                Solve(num + 1, temp);
                checked[i]++;
            }
            if (i == 1)
            {
                temp -= v[num];
                checked[i]--;
                Solve(num + 1, temp);
                checked[i]++;
            }
            if (i == 2)
            {
                temp *= v[num];
                checked[i]--;
                Solve(num + 1, temp);
                checked[i]++;
            }
            if (i == 3)
            {
                temp /= v[num];
                checked[i]--;
                Solve(num + 1, temp);
                checked[i]++;
            }
        }
    }
}

int main()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        int input;
        scanf("%d", &input);
        v.push_back(input);
    }
    for (int i = 0; i < 4; i++)
    {
        int input;
        scanf("%d", &input);
        checked[i] = input;
    }

    Max = 0x80000000;
    Min = 0x7fffffff;
    Solve(1, v[0]);
    printf("%d\n%d", Max, Min);
}