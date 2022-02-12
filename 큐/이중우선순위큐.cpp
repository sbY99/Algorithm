#include <iostream>
#include <set>

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);

    int T, K;
    cin >> T;

    for (int i = 0; i < T; i++)
    {
        cin >> K;
        multiset<int> s;

        for (int j = 0; j < K; j++)
        {
            char input;
            int num;
            cin >> input >> num;
            if (s.empty())
            {
                if (input == 'I')
                {
                    s.insert(num);
                }
            }
            else
            {
                if (input == 'I')
                {
                    s.insert(num);
                }
                else
                {
                    // s.end()는 마지막+1을 반환하므로
                    if (num == 1)
                    {
                        s.erase(--s.end());
                    }
                    else
                    {
                        s.erase(s.begin());
                    }
                }
            }
        }
        if (s.empty())
            cout << "EMPTY" << '\n';
        else
        {
            multiset<int>::iterator max, min;
            max = --s.end();
            min = s.begin();
            cout << *max << ' ' << *min << '\n';
        }
    }
    return 0;
}