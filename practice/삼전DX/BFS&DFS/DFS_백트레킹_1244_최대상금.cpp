#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;
int result;
int visit[1000000][11];

int len;
int toNumber(string s)
{
    int temp = 0;
    for (int i = 0; i < s.size(); i++)
    {
        temp = temp * 10 + s[i] - '0';
    }
    return temp;
}

void Len(string tmp)
{
    len = tmp.size();
}
void dfs(string tmp, int cnt)
{

    if (cnt == 0)
    {
        int temp = toNumber(tmp);
        if (temp > result)
            result = temp;
        return;
    }

    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            swap(tmp[i], tmp[j]);
            if (visit[toNumber(tmp)][cnt] == 0)
            {
                visit[toNumber(tmp)][cnt] = 1;
                dfs(tmp, cnt - 1);
            }

            swap(tmp[i], tmp[j]);
        }
    }
}

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int t, count;
    string num;
    cin >> t;
    for (int tc = 1; tc <= t; tc++)
    {
        cin >> num >> count; //정보판,교환 횟수
        result = 0;
        len = 0;
        memset(visit, 0, sizeof(visit));
        Len(num);
        dfs(num, count);

        cout << "#" << tc << " " << result << "\n";
    }

    return 0;
}
