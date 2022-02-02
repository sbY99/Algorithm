#include <iostream>
#include <vector>

#define MAX 1001

using namespace std;

int N, M;
int Relation[MAX];
vector<pair<int, int> > V;

int Find(int x)
{
    if (Relation[x] == x)
        return x;
    else
        return Relation[x] = Find(Relation[x]);
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
    if (x > y)
        Relation[x] = p2;
    else
        Relation[y] = p1;
}

void Solve()
{
    for (int i = 0; i < V.size(); i++)
    {
        //서로 연결되어 있지 않다면
        if (SameParent(V[i].first, V[i].second) == false)
        {
            Union(V[i].first, V[i].second);
        }
    }
}

int main()
{
    cin >> N >> M;
    //관계를 본인 자신으로 초기화
    for (int i = 1; i <= N; i++)
    {
        Relation[i] = i;
    }
    for (int i = 1; i <= M; i++)
    {
        int input1, input2;
        cin >> input1 >> input2;
        V.push_back(make_pair(input1, input2));
    }
    Solve();
    int input1, input2;
    cin >> input1 >> input2;
    if (SameParent(input1, input2))
    {
        printf("YES");
    }
    else
    {
        printf("NO");
    }
    return 0;
}