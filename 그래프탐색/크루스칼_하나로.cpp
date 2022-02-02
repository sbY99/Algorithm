#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>

typedef long long ll;

#define MAX 1000 + 1
using namespace std;

struct Pos
{
    ll x;
    ll y;
};

ll N;
ll Answer;
ll Parent[MAX];

double E;
Pos P[MAX];
vector<pair<ll, pair<ll, ll> > > Edge;

void Init()
{
    memset(Parent, 0, sizeof(Parent));
    N = Answer = 0;
    E = 0.0;
    Edge.clear();
    for (int i = 0; i < MAX; i++)
    {
        P[i].x = -1;
        P[i].y = -1;
    }
}

ll Distance(int i, int j)
{
    ll dx = (P[i].x - P[j].x) * (P[i].x - P[j].x);
    ll dy = (P[i].y - P[j].y) * (P[i].y - P[j].y);
    return dx + dy;
}

void Input()
{
    cin >> N;

    for (int i = 1; i <= N; i++)
    {
        ll a;
        cin >> a;
        P[i].x = a;
    }
    for (int i = 1; i <= N; i++)
    {
        ll a;
        cin >> a;
        P[i].y = a;
    }
    for (int i = 1; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            ll Dlist = Distance(i, j);
            //입력받은 순서대로 노드 번호를 지정해줌. 1~N
            //Edge에는 (i번 노드와 j번 노드의 거리, (i,j))가 들어감
            Edge.push_back(make_pair(Dlist, make_pair(i, j)));
        }
    }
    cin >> E;
}

//재귀 방식으로 부모 노드 찾음
int Find(int x)
{
    if (Parent[x] == x)
        return x;
    //만약 부모의 값이 바뀌어 있을 경우 이렇게 해야 갱신됨
    else
        return Parent[x] = Find(Parent[x]);
}

bool SameParent(int x, int y)
{
    x = Find(x);
    y = Find(y);

    if (x != y)
        return false;
    else
        return true;
}

void Union(int x, int y)
{
    x = Find(x);
    y = Find(y);

    //작은 쪽이 부모로 설정
    if (x < y)
        Parent[y] = x;
    else
        Parent[x] = y;
}

void Solution()
{
    sort(Edge.begin(), Edge.end());
    //Parent 초기 설정
    for (int i = 1; i <= N; i++)
        Parent[i] = i;

    for (int i = 0; i < Edge.size(); i++)
    {
        //만일 거리 순으로 정렬된 Edge의 노드 쌍이 같은 부모가 아니라면,
        //즉 연결되어있지 않다면,
        if (SameParent(Edge[i].second.first, Edge[i].second.second) == false)
        {
            Union(Edge[i].second.first, Edge[i].second.second);
            Answer = Answer + Edge[i].first;
        }
    }
}

void Solve()
{
    int Tc;
    cin >> Tc;
    for (int T = 1; T <= Tc; T++)
    {
        Init();
        Input();
        Solution();

        cout << "#" << T << " " << (double)(Answer * E) << endl;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout << fixed;
    cout.precision(0);

    Solve();
    return 0;
}