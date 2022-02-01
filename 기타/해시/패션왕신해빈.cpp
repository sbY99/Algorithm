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
    }

    return 0;
}