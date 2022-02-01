//
//  2018313555_HW4C.c
//  3학년 1학기
//
//  Created by SB on 2021/11/11.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK 100

typedef struct {
    int items[MAX_STACK];
    int top;
} Stack;

void InitStack(Stack* pstack) {
    pstack->top = -1;
}

int IsSFull(Stack* pstack) {
    return pstack->top == MAX_STACK - 1;
}

int IsSEmpty(Stack* pstack) {
    return pstack->top == -1;
}

int SPeek(Stack* pstack) {
    if (IsSEmpty(pstack))
        exit(1); //error: empty stack
    return pstack->items[pstack->top];
}

void Push(Stack* pstack, int item) {
    if (IsSFull(pstack))
        exit(1); //error: stack full
    pstack->items[++(pstack->top)] = item;
}

int Pop(Stack* pstack) {
    if (IsSEmpty(pstack))
        exit(1); //error: empty stack
    int item = pstack->items[pstack->top];
    --(pstack->top);
    return item;
}
typedef enum
{
    false,
    true
} bool;

typedef struct _push{
    int push;
    int pop;
}Pushed;

typedef struct _GNode
{
    int id;
    char data;
    struct _GNode *next;
} GNode;

typedef struct
{
    int num;
    int edge;
    GNode **heads;
} Graph;

void CreateGraph(Graph *pgraph, int num, int edge, char data[]);

void DestroyGraph(Graph *pgraph);

void AddEdge(Graph *pgraph, int src, int dest);

void DFS(Graph *pgraph);

void GetInput(void);

int main()
{
    GetInput();
    
    return 0;
}

void GetInput(void)
{

    int node, edge, src, des;
    char *a;

    scanf("%d %d", &node, &edge);
    getchar();

    a = malloc(sizeof(char) * (node + 1));
    scanf("%s", a);
    getchar();

    Graph g;
    CreateGraph(&g, node, edge, a);
    for (int i = 0; i < edge; i++)
    {

        scanf("%d %d", &src, &des);
        AddEdge(&g, src, des);

        getchar();
    }

    DFS(&g);

    DestroyGraph(&g);
}


void CreateGraph(Graph *pgraph, int num, int edge, char data[])
{
    pgraph->num = num;
    pgraph->edge=edge;
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

void DFS(Graph *pgraph)
{

    Stack stack;
    bool *visited = (bool *)malloc(sizeof(bool) * pgraph->num);
    for (int i = 0; i < pgraph->num; i++)
    {
        visited[i] = false;
    }
    //노드 개수만큼 방문여부를 체크하는 bool형 배열을 만들음

    int index=0;
    Pushed *pushed=malloc(sizeof(Pushed)*pgraph->edge);
    // 푸쉬 값과 팝 값을 저장하는 구조체 배열
    
    InitStack(&stack);
    Push(&stack, 0);
    
    
    while (!IsSEmpty(&stack))
    {
        GNode *cur;
        int vtx = SPeek(&stack);
        Pop(&stack);

        if (visited[vtx]){
            //만약 방문한 노드라면 사이클임을 의미
            //사이클을 가능하게 하는 엣지를 제거하면 되기 때문에
            //해당 노드를 방문하게 했던 연결된 노드를 찾음
            for(int i=0;i<pgraph->edge;i++){
                if(vtx==pushed[i].pop){
                    printf("%d %d",pushed[i].push,pushed[i].pop);
                    printf("\n");
                    break;
                }
            }
            break;
        }
        
        else
        {
            visited[vtx] = true;
        }

        cur = pgraph->heads[vtx]->next;
        while(cur!=NULL){
            if(!visited[cur->id]){
                Push(&stack, cur->id);
                // 푸쉬된 값과, 푸쉬된 값이 방문됨으로써 스택에 들어가게 된 값을 묶어서 저장해줌
                pushed[index].push=vtx;
                pushed[index].pop=cur->id;
                index++;
            }
            cur=cur->next;
        }
    }
}

