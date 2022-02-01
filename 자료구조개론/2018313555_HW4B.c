#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stackqueue.h"
/* Modify from here */

/* Modify to here */

#define MAX_SIZE 100
typedef enum
{
    false,
    true
} bool;

typedef struct _GNode
{
    int id;
    char data;
    struct _GNode *next;
} GNode;

typedef struct
{
    int num;
    GNode **heads;
} Graph;

void CreateGraph(Graph *pgraph, int num, char data[]);

void DestroyGraph(Graph *pgraph);

void AddEdge(Graph *pgraph, int src, int dest);

void PrintGraph(Graph *pgraph);

void DFS(Graph *pgraph);

void BFS(Graph *pgraph);

void GetInput();

/* Modify from here */

void ascending(int a[], int n);

/* Modify to here */

int main()
{
    Graph g;

    CreateGraph(&g, 5, "ABCFC");

    AddEdge(&g, 0, 1);
    AddEdge(&g, 0, 2);
    AddEdge(&g, 0, 4);
    AddEdge(&g, 1, 2);
    AddEdge(&g, 2, 3);
    AddEdge(&g, 2, 4);
    AddEdge(&g, 3, 4);

    DFS(&g);
    BFS(&g);

    DestroyGraph(&g);
    
    // GetInput();

    /*
    5 7
    ABCFC
    0 1
    0 2
    0 4
    1 2
    2 3
    2 4
    3 4
    */
    return 0;
}

void GetInput()
{

    int node, edge, src, des;
    char *a;

    scanf("%d %d", &node, &edge);
    getchar();

    a = malloc(sizeof(char) * (node + 1));
    scanf("%s", a);
    getchar();

    Graph g;
    CreateGraph(&g, node, a);
    for (int i = 0; i < edge; i++)
    {

        scanf("%d %d", &src, &des);
        AddEdge(&g, src, des);

        getchar();
    }

    DFS(&g);
    BFS(&g);

    DestroyGraph(&g);
}

/* Modify from here */

void CreateGraph(Graph *pgraph, int num, char data[])
{
    pgraph->num = num;
    pgraph->heads = (GNode **)malloc(sizeof(GNode *) * num);
    //GNode에 대한 포인터 배열
    //GNode에 대한 포인터 * num의 크기를 가짐
    for (int i = 0; i < num; i++)
    {
        //num개의 더미노드 생성(헤드를 의미함)
        pgraph->heads[i] = (GNode *)malloc(sizeof(GNode));
        pgraph->heads[i]->data = data[i];
        pgraph->heads[i]->next = NULL;
    }
}

void DestroyGraph(Graph *pgraph)
{
    for (int i = 0; i < pgraph->num; i++)
    {
        GNode *cur = pgraph->heads[i];
        while (cur != NULL)
        {
            GNode *temp = cur;
            cur = cur->next;
            free(temp);
        }
    }
    free(pgraph->heads);
}

void AddEdge(Graph *pgraph, int src, int dest)
{
    GNode *newNode1, *newNode2, *cur;
    //노드를 생성하여 heads에 연결함으로써 연결을 표현함
    newNode1 = (GNode *)malloc(sizeof(GNode));
    newNode1->id = dest;
    newNode1->next = NULL;

    cur = pgraph->heads[src];
    //해당 노드의 헤드에 접근
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = newNode1;
    //연결리스트의 맨 마지막에 연결해줌
    //src번째 노드 연결리스트에 dest 노드 연결

    newNode2 = (GNode *)malloc(sizeof(GNode));
    newNode2->id = src;
    newNode2->next = NULL;

    cur = pgraph->heads[dest];
    //해당 노드의 헤드에 접근
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = newNode2;
    //dest번째 노드 연결리스트에 src 노드 연결
}

void PrintGraph(Graph *pgraph)
{
    int len = pgraph->num;
    for (int i = 0; i < len; i++)
    {
        char id = pgraph->heads[i]->data;
        GNode *cur = pgraph->heads[i]->next;
        printf("%c:", id);
        while (cur != NULL)
        {
            printf(" %d", cur->id);
            cur = cur->next;
        }
        printf("\n");
    }
}

void DFS(Graph *pgraph)
{

    Stack stack;
    bool *visited = (bool *)malloc(sizeof(bool) * pgraph->num);
    for (int i = 0; i < pgraph->num; i++)
    {
        visited[i] = false;
    }
    //노드 개수만큼 방문여부를 체크하는 bool형 배열을 만들음

    InitStack(&stack);
    Push(&stack, 0);

    while (!IsSEmpty(&stack))
    {
        GNode *cur;
        int vtx = SPeek(&stack);
        Pop(&stack);

        if (visited[vtx])
            continue;
        //만약 방문 했으면 반복문 재실행
        else
        {
            visited[vtx] = true;
            printf("%d ", vtx);
        }
        
        //방문 후 스택에 노드 삽입하는 과정
        //즉, 다음 노드 방문을 위한 준비
        cur = pgraph->heads[vtx]->next;

        int *temp = (int *)malloc(sizeof(int) * pgraph->num);
        for (int i = 0; i < pgraph->num; i++)
        {
            temp[i] = -1;
            //요소를 모두 -1로 초기화 하여
            //push 할 때 검사하도록
        }
        int i = 0;
        while (cur != NULL)
        {
            if (!visited[cur->id])
            {
                temp[i] = cur->id;
                //크기 순으로 정렬을 위해 배열에 담음
            }
            cur = cur->next;
            i++;
        }
        ascending(temp, pgraph->num);
        //temp를 오름차순으로 정렬

        for (int i = 0; i < pgraph->num; i++)
        {
            if (temp[i] != -1)
            { //만약 -1이면 무시함
                Push(&stack, temp[i]);
            }
        }

        free(temp);
    }
    printf("\n");
}

void BFS(Graph *pgraph)
{

    Queue queue;
    bool *visited = (bool *)malloc(sizeof(bool) * pgraph->num);
    for (int i = 0; i < pgraph->num; i++)
    {
        visited[i] = false;
    }

    InitQueue(&queue);
    EnQueue(&queue, 0);
    while (!IsQEmpty(&queue))
    {
        GNode *cur;
        int vtx = QPeek(&queue);
        DeQueue(&queue);

        if (visited[vtx])
            continue;
        else
        {
            visited[vtx] = true;
            printf("%d ", vtx);
        }
        cur = pgraph->heads[vtx]->next;

        int *temp = (int *)malloc(sizeof(int) * pgraph->num);
        for (int i = 0; i < pgraph->num; i++)
        {
            temp[i] = -1;
            //요소를 모두 -1로 초기화 하여
            //enqueue 할 때 검사하도록
        }
        int i = 0;
        while (cur != NULL)
        {
            if (!visited[cur->id])
            {
                temp[i] = cur->id;
                //크기 순으로 정렬을 위해 배열에 담음
            }
            cur = cur->next;
            i++;
        }
        ascending(temp, pgraph->num);
        //temp를 오름차순으로 정렬
        for (int i = 0; i < pgraph->num; i++)
        {
            if (temp[i] != -1)
            { //만약 -1이면 무시함
                EnQueue(&queue, temp[i]);
            }
        }
        free(temp);
    }
    printf("\n");
}

void ascending(int a[], int n)
{
    //dfs에서는 id를 큰 순서대로 방문해야 하므로
    //스택에는 id가 작은 것을 먼저 넣어야 함
    //bfs에서는 작은 순서대로 방문해야 함
    //큐에도 id가 작은 것을 먼저 넣어야 함
    //즉 오름차순으로 정렬함
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

/* Modify to here */
