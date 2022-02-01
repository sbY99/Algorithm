#include <stdio.h>

typedef struct _Node
{
    int data;
    struct _Node *next;
} Node;

Node node[2000];
Node head, tail;
int nodeCnt;

void init();
Node *getNode(int data);
void insert2Head(int len);
void insert2Mid(int index, int data);
void deleteNode(int index);
void changeData(int index, int data);
void print(int n);

int main(int argc, char **argv)
{
    int test_case;
    int T, i;
    int len, count, idx;
    int index, value;
    char command;
    scanf("%d", &T);
    getchar();
    for (test_case = 1; test_case <= T; ++test_case)
    {
        init();
        scanf("%d %d %d", &len, &count, &idx);
        getchar();
        insert2Head(len);
        getchar();

        //커맨드 횟수만큼 반복
        for (i = 0; i < count; i++)
        {
            //커맨드 입력
            scanf(" %c", &command);
            switch (command)
            {
            case 'I':
                scanf("%d %d", &index, &value);
                insert2Mid(index, value);
                break;
            case 'D':
                scanf("%d", &index);
                deleteNode(index);
                break;
            case 'C':
                scanf("%d %d", &index, &value);
                changeData(index, value);
                break;
            }
            getchar();
        }
        //idx번째 요소 출력
        printf("#%d ", test_case);
        print(idx);
    }
    return 0;
}

void init()
{
    nodeCnt = 0;
    head.next = &tail;
    tail.next = NULL;
}

Node *getNode(int data)
{
    node[nodeCnt].data = data;
    node[nodeCnt].next = NULL;
    return &node[nodeCnt++];
}

void insert2Head(int len)
{
    Node *ptr = &head;
    int data;
    for (int j = 0; j < len; j++)
    {
        scanf("%d", &data);
        ptr->next = getNode(data);
        ptr = ptr->next;
    }
    //위 반복문이 끝나면 ptr은 마지막 노드를 가리킴
    ptr->next = &tail;
}

void insert2Mid(int index, int data)
{
    Node *ptr = &head;
    Node *New;
    //ptr은 삽입할 노드의 이전 노드
    for (int j = 0; j < index; j++)
    {
        ptr = ptr->next;
    }
    New = getNode(data);
    New->next = ptr->next;
    ptr->next = New;
}

void deleteNode(int index)
{
    Node *ptr = &head;
    //ptr은 삭제될 노드의 이전 노드
    for (int j = 0; j < index; j++)
    {
        ptr = ptr->next;
    }
    ptr->next = ptr->next->next;
}

void changeData(int index, int data)
{
    Node *ptr = &head;
    //ptr은 변경될 노드의 이전 노드
    for (int j = 0; j < index; j++)
    {
        ptr = ptr->next;
    }
    ptr->next->data = data;
}

//L없으면 -1 출력
void print(int n)
{
    Node *ptr = &head;
    int len = 0;

    //노드가 len 개면 n은 len-1 이하여야함
    while (ptr->next->next != NULL)
    {
        len++;
        ptr = ptr->next;
    }
    if (n > len)
    {
        printf("%d\n", -1);
        return;
    }
    else
    {
        ptr = &head;
        for (int i = 0; i < n; i++)
        {
            ptr = ptr->next;
        }
        printf("%d", ptr->next->data);
        printf("\n");
    }
}