#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<int> A;
vector<int> B;

bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
    scanf("%d", &N);
    int input;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &input);
        A.push_back(input);
    }
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &input);
        B.push_back(input);
    }
    sort(A.begin(), A.end());
    sort(B.begin(), B.end(), cmp);

    int result = 0;

    for (int i = 0; i < N; i++)
    {
        result += A[i] * B[i];
    }
    printf("%d", result);
    return 0;
}