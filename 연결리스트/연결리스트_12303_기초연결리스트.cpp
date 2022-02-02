#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum
{
    ADD_HEAD = 1,
    ADD_TAIL,
    ADD_NUM,
    REMOVE,
    PRINT,
    END = 99
};

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);

static void run()
{
    while (1)
    {
        int cmd, data, num, cnt, i;
        int output[MAX_NODE] = {0};

        scanf("%d", &cmd);
        switch (cmd)
        {
        case ADD_HEAD:
            scanf("%d", &data);
            addNode2Head(data);
            break;
        case ADD_TAIL:
            scanf("%d", &data);
            addNode2Tail(data);
            break;
        case ADD_NUM:
            scanf("%d %d", &data, &num);
            addNode2Num(data, num);
            break;
        case REMOVE:
            scanf("%d", &data);
            removeNode(data);
            break;
        case PRINT:
            cnt = getList(output);
            i = 0;
            while (cnt--)
                printf("%d ", output[i++]);
            printf("\n");
            break;
        case END:
            return;
        }
    }
}

int main(void)
{
    //setbuf(stdout, NULL);
    //freopen("sll_input.txt", "r", stdin);

    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++)
    {
        printf("#%d\n", t);
        init();
        run();
        printf("\n");
    }

    return 0;
}

////////////////////////////////////////

#define MAX_NODE 10000

struct Node
{
    int data;
    Node *next;
};

Node node[MAX_NODE];
int nodeCnt;
Node head, tail;

Node *getNode(int data)
{
    node[nodeCnt].data = data;
    node[nodeCnt].next = NULL;
    return &node[nodeCnt++];
}

void init()
{
    nodeCnt = 0;
    head.next = &tail;
    tail.next = NULL;
}

void addNode2Head(int data)
{
    Node *ptr = &head;
    Node *New = getNode(data);
    New->next = ptr->next;
    ptr->next = New;
}

void addNode2Tail(int data)
{
    Node *ptr = &head;
    //ptr은 tail의 이전 노드
    while (ptr->next->next)
    {
        ptr = ptr->next;
    }
    Node *New = getNode(data);
    ptr->next = New;
    New->next = &tail;
}

void addNode2Num(int data, int num)
{
    Node *ptr = &head;
    Node *New = getNode(data);
    //ptr은 삽입할 위치의 이전 노드
    //1-2-3-4.. 순이므로 -1필요
    while (num - 1 && ptr->next)
    {
        ptr = ptr->next;
        num--;
    }
    if (ptr->next == NULL)
    {
        return;
    }

    New->next = ptr->next;
    ptr->next = New;
}

void removeNode(int data)
{
    Node *ptr = &head;
    //ptr은 삭제될 노드의 이전 노드
    //ptr이 tail이면 종료
    while (ptr->next)
    {
        if (ptr->next->data == data)
        {
            break;
        }
        ptr = ptr->next;
    }
    if (ptr->next == NULL)
    {
        return;
    }
    ptr->next = ptr->next->next;
}

int getList(int output[MAX_NODE])
{
    //첫번째 노드 선택
    Node *ptr = head.next;
    int len = 0;
    //ptr->next가 null이면, 즉 ptr이 tail이면 종료
    while (ptr->next)
    {
        output[len++] = ptr->data;
        ptr = ptr->next;
    }
    return len;
}