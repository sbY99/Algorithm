#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

static unsigned int seed = 12345;
static unsigned int pseudo_rand(int max)
{
    seed = ((unsigned long long)seed * 1103515245 + 12345) & 0x7FFFFFFF;
    return seed % max;
}

#define MAX_N (40)
#define MAX_K (98)
#define MIN_N (2)
#define MAX_CHILD (5)

extern void dfs_init(int N, int path[MAX_N][2]);
extern int dfs(int k);

static int p[MAX_K + 2];
static int c[MAX_K + 2];
static int path[MAX_N][2];
static void makeTree(int n)
{
    for (int i = 1; i < MAX_K + 2; ++i)
    {
        p[i] = c[i] = -1;
    }
    c[pseudo_rand(MAX_K + 1) + 1] = 0;
    for (int i = 0; i < n; ++i)
    {
        int pi = pseudo_rand(MAX_K + 1) + 1;
        while (c[pi] < 0 || c[pi] >= MAX_CHILD)
        {
            ++pi;
            if (pi == MAX_K + 2)
                pi = 1;
        }
        int ci = pseudo_rand(MAX_K + 1) + 1;
        while (c[ci] >= 0)
        {
            ++ci;
            if (ci == MAX_K + 2)
                ci = 1;
        }
        p[ci] = pi;
        ++c[pi];
        c[ci] = 0;
    }
    bool check[MAX_K + 2] = {false};
    for (int i = 0; i < n; ++i)
    {
        int e = pseudo_rand(MAX_K + 1) + 1;
        while (check[e] || c[e] < 0 || p[e] == -1)
        {
            ++e;
            if (e == MAX_K + 2)
                e = 1;
        }
        check[e] = true;
        path[i][0] = p[e];
        path[i][1] = e;
    }
}

int main()
{
    setbuf(stdout, NULL);
    int T;
    //freopen("dfs_input.txt", "r", stdin);
    scanf("%d", &T);

    int totalScore = 0;
    for (int tc = 1; tc <= T; tc++)
    {
        int n, q;

        scanf("%d %d %d", &n, &q, &seed);

        makeTree(n - 1);
        dfs_init(n, path);

        bool check[MAX_K + 2] = {false};
        int score = 100;
        for (int i = 0; i < q; ++i)
        {
            int k, ret, correct;

            scanf("%d", &k);

            ret = dfs(k);
            printf("dd: %d\n", ret);
            scanf("%d", &correct);

            if (ret != correct)
                score = 0;
        }
        printf("#%d : %d\n", tc, score);
        totalScore += score;
    }

    printf("#total score : %d\n", totalScore / T);

    return 0;
}

//////////////////////////

int Graph[100][100];
int Num[100];

void dfs_init(int N, int path[100][2])
{
    for (int i = 0; i < 100; i++)
    {
        Num[i] = 0;
        for (int j = 0; j < 100; j++)
        {
            Graph[i][j] = 0;
        }
    }
    /*
    memset(visited, false, sizeof(visited));
    memset(Graph, 0, sizeof(Graph));
    memset(path, 0, sizeof(path));
    */

    //방향 그래프이기 때문에 부모 행, 자식 열에만 1 삽입
    for (int i = 0; i < N; i++)
    {
        //부모 행의 0번 인덱스부터 자식 번호를 채워나감
        Graph[path[i][0]][Num[path[i][0]]++] = path[i][1];
    }
}

int result;
int Top;
int Stack[100];

int dfs(int n)
{
    int Visited[100] = {0};
    Top = -1;
    result = -1;
    Stack[++Top] = n;
    while (Top != -1)
    {
        int curr = Stack[Top--];
        if (!Visited[curr])
        {
            //방문 노드가 n보다 크다면,
            //즉 후보 자식이라면
            if (curr > n)
            {
                return curr;
            }
            Visited[curr] = 1;

            //개수-1인덱스부터 0까지(순서대로 쌓이므로 역순으로 스택에 넣음)
            for (int i = Num[curr] - 1; i >= 0; i--)
            {
                Stack[++Top] = Graph[curr][i];
            }
        }
    }

    return result;
}
