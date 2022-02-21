#include <iostream>
#include <cmath>

using namespace std;

int N;
int Max;
int arr[1001];
int check[1001];

void Solve()
{
    for (int i = 1; i <= N; i++)
    {
        int temp = 0;
        for (int j = i - 1; j >= 0; j--)
        {
            // 이전에 입력받은 값 중
            // 자신보다 작은 값 찾기
            if (arr[i] > arr[j])
            {
                temp = max(temp, check[j] + 1);
            }
        }
        check[i] = temp;
        if (check[i] > Max)
        {
            Max = check[i];
        }
    }
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        scanf("%d", &arr[i]);
    }
    Solve();
    printf("%d", Max);
}