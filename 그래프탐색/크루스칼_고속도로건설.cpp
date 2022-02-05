#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
#define MAX 50001

#include <iostream>

using namespace std;
int N, M;
int Parent[MAX];
int result;
vector<pair<int, pair<int, int> > > Edge;

void init()
{
    for (int i = 1; i < MAX; i++)
    {
        Parent[i] = i;
    }
    result = 0;
    Edge.clear();
}

int findParent(int x)
{
    if (Parent[x] == x)
        return x;
    else
        return Parent[x] = findParent(Parent[x]);
}

bool isSame(int x, int y)
{
    int parent_x = findParent(x);
    int parent_y = findParent(y);
    if (parent_x == parent_y)
        return true;
    else
        return false;
}

void Union(int x, int y)
{
    int parent_x = findParent(x);
    int parent_y = findParent(y);

    if (parent_x < parent_y)
        Parent[parent_y] = parent_x;
    else
        Parent[parent_x] = parent_y;
}

void solution()
{
    cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int node1, node2, dis;
        cin >> node1 >> node2 >> dis;
        Edge.push_back(make_pair(dis, make_pair(node1, node2)));
    }

    sort(Edge.begin(), Edge.end());

    for (int i = 0; i < Edge.size(); i++)
    {
        if (isSame(Edge[i].second.first, Edge[i].second.second) == false)
        {
            Union(Edge[i].second.first, Edge[i].second.second);
            result += Edge[i].first;
        }
    }
}

int main(int argc, char **argv)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int test_case;
    int T;

    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        init();
        solution();
        printf("#%d %d\n", test_case, result);
    }
    return 0;
}