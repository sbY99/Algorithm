#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int Input[10000001];
vector<int> Count;
int input;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &input);
        Input[i] = input;
        Count.push_back(input);
    }
    sort(Count.begin(), Count.end());
    Count.erase(unique(Count.begin(), Count.end()), Count.end());

    for (int i = 0; i < N; i++)
    {
        printf("%d ", lower_bound(Count.begin(), Count.end(), Input[i]) - Count.begin());
    }
    return 0;
}
