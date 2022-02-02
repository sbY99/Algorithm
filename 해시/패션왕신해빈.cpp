#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main()
{
    int T, N;
    scanf("%d", &T);
    for (int i = 0; i < T; i++)
    {
        cin >> N;
        map<string, int> M;

        for (int j = 0; j < N; j++)
        {
            string name, type;
            cin >> name >> type;
            M[type]++;
        }

        int count = 1;
        map<string, int>::iterator iter;
        for (iter = M.begin(); iter != M.end(); iter++)
        {
            count *= ((iter->second) + 1);
        }
        printf("%d\n", count - 1);
    }

    return 0;
}