#include <iostream>
#include <vector>

using namespace std;

#define Max 100000 + 1

int N;
bool visited[Max];
int parent[Max];
vector<int> tree[Max];

void findParent(int nodeNum)
{
    visited[nodeNum] = true; //방문한 노드 표시

    for (int i = 0; i < tree[nodeNum].size(); i++)
    {
        int next = tree[nodeNum][i];
        if (!visited[next])
        {
            parent[next] = nodeNum; // next의 parent는 nodeNum
            findParent(next);
        }
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> N;

    for (int i = 0; i < N - 1; i++)
    {
        int node1, node2;
        cin >> node1 >> node2;
        tree[node1].push_back(node2);
        tree[node2].push_back(node1);
    }
    findParent(1);

    for (int i = 2; i <= N; i++)
        cout << parent[i] << "\n";

    return 0;
}
