#include <iostream>

using namespace std;

int N, M;
string S;

int result;

int main()
{
    cin >> N >> M;
    cin >> S;

    for (int i = 0; i < M; i++)
    {
        int l = 0;
        if (S[i] == 'O')
        {
            continue;
        }
        else
        {
            while (S[i + 1] == 'O' && S[i + 2] == 'I')
            {
                l++;
                if (l == N)
                {
                    result++;
                    l--;
                }
                i += 2;
            }
        }
    }
    printf("%d", result);
    return 0;
}