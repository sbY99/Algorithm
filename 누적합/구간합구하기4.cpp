#include <iostream>

#define MAX 100001
using namespace std;

int arr[MAX];

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int N, M;
    int input;
    cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        cin >> input;
        arr[i] = arr[i - 1] + input;
    }
    int start;
    int end;
    int result;
    for (int i = 1; i <= M; i++)
    {
        cin >> start >> end;
        result = arr[end] - arr[start - 1];
        printf("%d\n", result);
    }

    return 0;
}