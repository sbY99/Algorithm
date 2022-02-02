#include <iostream>

using namespace std;
#define MAX_POOL 10000
#define MAX_NODE 10000

int memPoolCnt;

struct ListNode //각 노드의 아이디를 가지고 있으며, 트리 노드에서 자식끼리 연결해줌
{
    int id;
    ListNode *prev;
} listPool[MAX_POOL];

struct TreeNode //tree의 각 정보를 담고 있음
{
    int parent;
    ListNode *child; // parent를 인덱스로 하는 노드에서 가장 최근에 추가된 자식 노드 가리킴
} treeNode[MAX_NODE];

void init()
{
    memPoolCnt = 0;
    for (int i = 0; i < MAX_NODE; i++)
    {
        treeNode[i].parent = -1;
        treeNode[i].child = NULL;
    }
}

void insertNode(int parent, int child)
{
    treeNode[child].parent = parent; //child 노드에서 부모 ID 저장

    ListNode *node = &listPool[memPoolCnt++]; //메모리 풀에서 공간 할당받음. 연결리스트와 방식 비슷
    node->id = child;
    node->prev = treeNode[parent].child; //parent 노드의 child 리스트에 연결
    treeNode[parent].child = node;       //마지막 child 갱신
}

int findRoot(int n)
{
    //루트노드의 parent는 초기 값인 -1
    while (treeNode[n].parent != -1)
    {
        n = treeNode[n].parent;
    }
    return n;
}

void traverse(int cur)
{
    cout << cur << " ";
    for (ListNode *l = treeNode[cur].child; l != NULL; l = l->prev)
    {
        traverse(l->id); //재귀를 통한 dfs
    }
}