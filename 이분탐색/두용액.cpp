#include <iostream>
#include <algorithm>

using namespace std;
int N;
int arr[100001];

void init();
void input();
bool isNear(int left, int right, int sum);
void solve();

void init()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
}

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
    }
}

bool isNear(int left, int right, int sum)
{
    int temp = arr[left] + arr[right];

    if (temp >= 0)
    {
        if (sum >= 0)
        {
            if (sum > temp)
                return true;
            else
                return false;
        }
        else
        {
            if (sum * -1 > temp)
                return true;
            else
                return false;
        }
    }
    else
    {
        if (sum >= 0)
        {
            if (sum > temp * -1)
                return true;
            else
                return false;
        }
        else
        {
            if (sum * -1 > temp * -1)
                return true;
            else
                return false;
        }
    }
}

void solve()
{
    sort(arr, arr + N);

    int left = 0;
    int right = N - 1;
    int sum = 2000000001;

    int r1, r2;

    while (left < right)
    {
        if (isNear(left, right, sum))
        {
            r1 = arr[left];
            r2 = arr[right];

            sum = arr[left] + arr[right];
        }

        if (arr[left] + arr[right] > 0)
        {
            right--;
        }
        else if (arr[left] + arr[right] == 0)
        {
            cout << arr[left] << " " << arr[right];
            return;
        }
        else
        {
            left++;
        }
    }
    cout << r1 << " " << r2;
}

int main()
{
    init();
    input();
    solve();

    return 0;
}