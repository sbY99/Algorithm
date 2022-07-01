#include <iostream>
#include <vector>

using namespace std;

int K;
vector<int> stack;

int main()
{
    cin >> K;

    int num, sum = 0;
    for (int i = 0; i < K; i++)
    {
        cin >> num;

        if (num != 0)
            stack.push_back(num);
        else
            stack.pop_back();
    }

    for (int i = 0; i < stack.size(); i++)
    {
        sum += stack[i];
    }

    cout << sum;

    return 0;
}