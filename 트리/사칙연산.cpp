#include <iostream>

#define MAX 1001
using namespace std;

struct Node
{
    char op;
    int id;
    Node *left;
    Node *right;
};

int N;
int queue_idx;
double Queue[MAX];
Node Tree[MAX];

Node *getNode(int idx)
{
    return &Tree[idx];
}

void CreateNode(int idx, char op, int id, int left, int right)
{
    Node *newNode = getNode(idx);
    newNode->op = op;
    newNode->id = id;
    newNode->left = getNode(left);
    newNode->right = getNode(right);
}

void Init()
{
    queue_idx = 0;
    for (int i = 0; i < MAX; i++)
    {
        Tree[i].left = NULL;
        Tree[i].right = NULL;
        Queue[i] = 0.0;
    }
}

void Input()
{
    int idx, left, right;
    char op;
    int id;
    cin >> idx;

    char check[10];
    cin >> check;

    if ('0' <= check[0] && check[0] <= '9')
    {
        int num = 0;
        for (int i = 0; check[i]; i++)
        {
            num *= 10;
            num += check[i] - '0';
        }
        id = num;
        //없는 값은 0 처리
        left = right = op = 0;
    }

    else
    {
        op = check[0];
        cin >> left >> right;
        //없는 값은 0처리
        id = 0;
    }

    CreateNode(idx, op, id, left, right);
}

void Calc(Node *node)
{
    //연산자 가짐
    if (node->id == 0)
    {
        Calc(node->left);
        Calc(node->right);
        double n2 = Queue[queue_idx--];
        double n1 = Queue[queue_idx--];
        double temp;
        switch (node->op)
        {
        case '+':
            temp = n1 + n2;
            break;
        case '-':
            temp = n1 - n2;
            break;
        case '*':
            temp = n1 * n2;
            break;
        case '/':
            temp = n1 / n2;
            break;
        }
        Queue[++queue_idx] = temp;
    }
    //숫자 가짐
    else
    {
        Queue[++queue_idx] = node->id;
    }
}

int main()
{
    int test_case;
    for (test_case = 1; test_case <= 10; ++test_case)
    {
        Init();

        cin >> N;
        for (int i = 0; i < N; i++)
        {
            Input();
        }
        Calc(&Tree[1]);
        int result = Queue[1];
        printf("#%d %d\n", test_case, result);
    }
    return 0;
}