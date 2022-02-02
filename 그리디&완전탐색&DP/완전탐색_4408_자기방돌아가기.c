#include <stdio.h>

typedef struct _Node
{
    int depart;
    int arrival;
    struct _Node *next;
} Node;

Node node[400];
Node head, tail;
int nodeCnt;
int count;

void init();
Node *getNode(int depart, int arrival);
void insert2Head(int len);
void getCount(int len);

int main(void)
{
    int test_case;
    int T, len;
    setbuf(stdout, NULL);
    scanf("%d", &T);
    getchar();
    for (test_case = 1; test_case <= T; ++test_case)
    {
        init();
        scanf("%d", &len);
        getchar();
        insert2Head(len);
        printf("#%d %d\n", test_case, count);
    }
    return 0;
}

void init()
{
    nodeCnt = 0;
    head.next = &tail;
    tail.next = NULL;
    count = 0;
}

Node *getNode(int depart, int arrival)
{
    node[nodeCnt].depart = depart;
    node[nodeCnt].arrival = arrival;
    node[nodeCnt].next = NULL;
    return &node[nodeCnt++];
}

void insert2Head(int len)
{
    Node *ptr = &head;
    int depart, arrival;
    for (int j = 0; j < len; j++)
    {
        scanf("%d %d", &depart, &arrival);
        getchar();
        ptr->next = getNode(depart, arrival);
        ptr = ptr->next;
    }
    //위 반복문이 끝나면 ptr은 마지막 노드를 가리킴
    ptr->next = &tail;

    Node *p = head.next;
    getCount(len);
}

void getCount(int len)
{
    Node *ptr;
    Node *temp = &head;
    int min, max, swap;
    int from, to;

    while (len)
    {
        ptr = head.next;
        //첫 노드의 데이터
        min = ptr->depart, max = ptr->arrival;
        if (min > max)
        {
            swap = min;
            min = max;
            max = swap;
        }
        //max가 홀 인 경우
        if ((max & 1))
        {
            //큰 값을 증가시켜줌
            max++;
        }
        //min이 짝 인 경우
        if (!(min & 1))
        {
            //작은 값을 감소시켜줌
            min--;
        }

        //ptr 이후가 tail이면 종료
        while (ptr->next->next != NULL)
        {
            from = ptr->next->depart, to = ptr->next->arrival;
            //다음 노드가 범위에 걸치지 않는다면 count하지 않음
            //len 감소 후 노드 삭제
            if ((from < min && to < min) || (to > max && from > max))
            {
                ptr->next = ptr->next->next;
                len--;
                //노드 제거했을때 이후 노드가 tail이라면 종료
                continue;
            }
            ptr = ptr->next;
        }

        //첫 노드 삭제 후 횟수 1증가
        temp->next = temp->next->next;
        len--;
        count++;
    }
}