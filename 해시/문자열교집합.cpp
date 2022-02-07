#include <iostream>
#include <unordered_set>

using namespace std;

unordered_set<string> s;

int main()
{
    int test_case;
    int T, N, M, Cnt = 0;
    char tmp[51];
    scanf("%d", &T);
    for (test_case = 1; test_case <= T; ++test_case)
    {
        s.clear();
        scanf("%d %d", &N, &M);
        int Cnt = 0;
        for (int i = 0; i < N; i++)
        {
            scanf("%s", tmp);
            s.insert(string(tmp));
        }
        for (int i = 0; i < M; i++)
        {
            scanf("%s", tmp);
            if (s.find(string(tmp)) != s.end())
            {
                Cnt++;
            }
        }
        printf("#%d %d\n", test_case, Cnt);
    }
}