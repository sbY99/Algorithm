#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define Max 100000 + 1

struct Grade
{
    int A;
    int B;
};

vector<struct Grade> v;
int Discount;
int N;

bool cmp(Grade X, Grade Y)
{
    if (X.A < Y.A)
    {
        return true;
    }
    return false;
}

void init()
{
    v.clear();
    Discount = 0;
}

void Solve()
{
    sort(v.begin(), v.end(), cmp);
    int min = 1000001;
    for (int i = 0; i < N; i++)
    {
        if (v[i].B > min)
            Discount++;
        else
            min = v[i].B;
    }
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        init();
        int a, b;
        scanf("%d", &N);
        for (int j = 0; j < N; j++)
        {
            scanf("%d %d", &a, &b);
            Grade temp;
            temp.A = a;
            temp.B = b;

            v.push_back(temp);
        }
        Solve();
        printf("%d\n", N - Discount);
    }

    return 0;
}