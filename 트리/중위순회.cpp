#include <iostream>
#include <string>

using namespace std;
#define MAX_NODE 101

struct Node
{
    char Id;
    Node *leftNode;
    Node *rightNode;
};

Node NodeList[MAX_NODE];
int Cnt;
int N;

void init()
{
    Cnt = 0;
    for (int i = 0; i < MAX_NODE; i++)
    {
        NodeList[i].leftNode = NULL;
        NodeList[i].rightNode = NULL;
    }
}

Node *getNode(int idx)
{
    return &NodeList[idx];
}

void CreateNode(char id, int left, int right)
{
    Node *node = getNode(++Cnt);
    node->Id = id;
    node->leftNode = getNode(left);
    node->rightNode = getNode(right);
}

void Input()
{

    for (int i = 1; i <= N; i++)
    {
        int num, left = 0, right = 0;
        char id;
        cin >> num >> id;

        if (num * 2 < N)
        {
            cin >> left >> right;
        }
        else if (num * 2 == N)
        {
            cin >> left;
        }
        CreateNode(id, left, right);
    }
}

void inorder(Node *node)
{
    if (node->leftNode != NULL)
    {
        if (node->leftNode->Id != 0)
        {
            inorder(node->leftNode);
        }
    }
    printf("%c", node->Id);
    if (node->rightNode != NULL)
    {
        if (node->rightNode->Id != 0)
        {
            inorder(node->rightNode);
        }
    }
}

int main()
{
    int test_case;
    for (test_case = 1; test_case <= 10; ++test_case)
    {
        cin >> N;
        init();
        Input();
        printf("#%d ", test_case);
        inorder(&NodeList[1]);
        printf("\n");
    }
    return 0;
}