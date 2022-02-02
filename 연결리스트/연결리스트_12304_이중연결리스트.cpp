#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_NODE 10000

enum
{
    ADD_HEAD = 1,
    ADD_TAIL,
    ADD_NUM,
    FIND,
    REMOVE,
    PRINT,
    PRINT_REVERSE,
    END = 99
};

extern void init();
extern void addNode2Head(int data);
extern void addNode2Tail(int data);
extern void addNode2Num(int data, int num);
extern int findNode(int data);
extern void removeNode(int data);
extern int getList(int output[MAX_NODE]);
extern int getReversedList(int output[MAX_NODE]);

static void run()
{
    while (1)
    {
        int cmd, data, num, cnt, i = 0;
        int output[MAX_NODE] = {0};

        scanf("%d", &cmd);
        switch (cmd)
        {
        case ADD_HEAD: // 1
            scanf("%d", &data);
            addNode2Head(data);
            break;
        case ADD_TAIL: // 2
            scanf("%d", &data);
            addNode2Tail(data);
            break;
        case ADD_NUM: // 3
            scanf("%d %d", &data, &num);
            addNode2Num(data, num);
            break;
        case FIND: // 4
            scanf("%d", &data);
            num = findNode(data);
            printf("%d\n", num);
            break;
        case REMOVE: // 5
            scanf("%d", &data);
            removeNode(data);
            break;
        case PRINT: // 6
            cnt = getList(output);
            while (cnt--)
                printf("%d ", output[i++]);
            printf("\n");
            break;
        case PRINT_REVERSE: // 7
            cnt = getReversedList(output);
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
    //freopen("dll_input.txt", "r", stdin);

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

///////////////////////////////////////////

#define MAX_NODE 10000

struct Node
{
    int data;
    Node *prev;
    Node *next;
};

Node node[MAX_NODE];
int nodeCnt;
Node head, tail;

Node *getNode(int data)
{
    node[nodeCnt].data = data;
    node[nodeCnt].prev = NULL;
    node[nodeCnt].next = NULL;
    return &node[nodeCnt++];
}


void init()
{
    nodeCnt = 0;
    head.prev = NULL;
    head.next = &tail;
    tail.prev = &head;
    tail.next = NULL;
}

void addNode2Head(int data)
{
    Node *ptr = &head;
    Node *New = getNode(data);
    New->next = ptr->next;
    New->prev = &head;
    ptr->next->prev = New;
    ptr->next = New;
}

void addNode2Tail(int data)
{
    Node *ptr = &head;
    Node *New = getNode(data);
    //ptr은 tail
    while (ptr->next)
    {
        ptr = ptr->next;
    }
    New->next = ptr;
    New->prev = ptr->prev;
    ptr->prev->next = New;
    ptr->prev = New;
}

void addNode2Num(int data, int num)
{
    Node *ptr = &head;
    Node *New = getNode(data);
    int idx = num;
    //1-2-3..순으로 시작하므로
    //ptr은 삽입 노드의 이전 노드
    while (ptr->next)
    {
        if (idx == 1)
        {
            break;
        }
        ptr = ptr->next;
        idx--;
    }
    //ptr이 tail이면 비정상적 종료
    if (ptr->next == NULL)
    {
        return;
    }
    New->prev = ptr;
    New->next = ptr->next;
    ptr->next->prev = New;
    ptr->next = New;
}

int findNode(int data)
{
    Node *ptr = head.next;
    int idx = 1;
    while (ptr->data != data)
    {
        ptr = ptr->next;
        idx++;
    }
    return idx;
}

void removeNode(int data)
{
    Node *ptr = &head;
    //ptr은 삭제될 노드의 이전 노드
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
    ptr->next->next->prev = ptr;
    ptr->next = ptr->next->next;
}

int getList(int output[MAX_NODE])
{
    Node *ptr = head.next;
    int len = 0;
    //ptr이 tail이면 중단
    while (ptr->next)
    {
        output[len++] = ptr->data;
        ptr = ptr->next;
    }
    return len;
}

int getReversedList(int output[MAX_NODE])
{
    Node *ptr = tail.prev;
    int len = 0;
    //ptr이 head면 중단
    while (ptr->prev)
    {
        output[len++] = ptr->data;
        ptr = ptr->prev;
    }
    return len;
}