
#include <stdio.h>

typedef struct _Node
{
    int data;
    struct _Node *prev;
    struct _Node *next;

} Node;

Node node[1000000];
Node head, tail;
int nodeCnt;

void init();
Node *getNode(int data);
void inserting(Node *ptr, Node *New);
void insertNode(int idx, int len);
void deleteNode(int idx, int len);
void add2EndNode(int len);
void print();

int main()
{
    int test_case;
    int T = 1;
    int len_input, len_command;
    int idx, len;
    char command;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        init();
        //원본 암호문 길이 입력
        scanf("%d", &len_input);
        getchar();
        //원본 암호문 입력(앞에서 0의 위치는 맨 앞을 의미)
        insertNode(0, len_input);
        getchar();
        //명령어 개수 입력
        scanf("%d", &len_command);
        getchar();
        for (int i = 0; i < len_command; i++)
        {
            scanf(" %c", &command);
            switch (command)
            {
            case 'I':
                scanf("%d %d", &idx, &len);
                insertNode(idx, len);
                break;
            case 'D':
                scanf("%d %d", &idx, &len);
                deleteNode(idx, len);
                break;
            case 'A':
                scanf("%d", &len);
                add2EndNode(len);
                break;
            }
        }
        getchar();
        printf("#%d ", test_case);
        print();
    }
    return 0;
}

void init()
{
    nodeCnt = 0;
    head.prev = NULL;
    head.next = &tail;
    tail.prev = &head;
    tail.next = NULL;
}

Node *getNode(int data)
{
    node[nodeCnt].data = data;
    node[nodeCnt].prev = NULL;
    node[nodeCnt].next = NULL;
    return &node[nodeCnt++];
}

//0-1-2..순서. 즉, 맨 앞이 0
void insertNode(int idx, int len)
{
    int data;
    Node *ptr = &head;
    Node *New;
    //ptr은 삽입될 위치의 이전 노드
    for (int i = 0; i < idx; i++)
    {
        ptr = ptr->next;
    }

    for (int i = 0; i < len; i++)
    {
        scanf("%d", &data);
        New = getNode(data);
        inserting(ptr, New);
        ptr = ptr->next;
    }
}

void inserting(Node *ptr, Node *New)
{
    New->next = ptr->next;
    New->prev = ptr;
    ptr->next->prev = New;
    ptr->next = New;
}

void deleteNode(int idx, int len)
{
    Node *ptr = &head;
    Node *newNext;
    //ptr은 삭제 시작 노드의 이전 노드
    for (int i = 0; i < idx; i++)
    {
        ptr = ptr->next;
    }
    newNext = ptr->next;
    //newNext는 삭제 끝 노드의 다음 노드
    //즉, ptr과 newNext를 연결해줌
    for (int i = 0; i < len; i++)
    {
        newNext = newNext->next;
    }
    ptr->next = newNext;
    newNext->prev = ptr;
}

void add2EndNode(int len)
{
    int data;
    Node *ptr = tail.prev;
    Node *New;
    //ptr은 삽입될 위치의 이전 노드
    for (int i = 0; i < len; i++)
    {
        scanf("%d", &data);
        New = getNode(data);
        inserting(ptr, New);
        ptr = ptr->next;
    }
}

void print()
{
    Node *ptr = head.next;
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}