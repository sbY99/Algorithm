#include <iostream>
#include <vector>
#include <set>

using namespace std;

int N, M;
int parent[1001];
vector<pair<int, int> > v;

int Find(int x)
{
    if (parent[x] == x)
        return x;
    else
        return parent[x] = Find(parent[x]);
}

bool SameParent(int x, int y)
{
    int p1 = Find(x);
    int p2 = Find(y);
    if (p1 == p2)
        return true;
    else
        return false;
}

void Union(int x, int y)
{
    int p1 = Find(x);
    int p2 = Find(y);
    if (p1 < p2)
        parent[p2] = p1;

    else
        parent[p1] = p2;
}

int main()
{
    cin >> N >> M;

    for (int i = 1; i <= N; i++)
    {
        parent[i] = i;
    }

    for (int i = 1; i <= M; i++)
    {
        int input1, input2;
        cin >> input1 >> input2;
        v.push_back(make_pair(input1, input2));
    }

    for (int i = 0; i < v.size(); i++)
    {
        if (SameParent(v[i].first, v[i].second) == false)
        {
            Union(v[i].first, v[i].second);
        }
    }

    set<int> check;
    for (int i = 1; i <= N; i++)
    {
        check.insert(Find(i));
    }

    printf("%d", check.size());
    return 0;
}