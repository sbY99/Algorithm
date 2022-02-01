#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> V;

int main()
{
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        int input;
        cin >> input;
        V.push_back(input);
    }
    sort(V.begin(), V.end());

    for (int i = 1; i < V.size(); i++)
    {
        V[i] += V[i - 1];
    }

    int result = 0;
    for (int i = 0; i < V.size(); i++)
    {
        result += V[i];
    }
    printf("%d", result);
    return 0;
}