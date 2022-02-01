#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
typedef enum
{
    false,
    true
} bool;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
#define MALE 0
#define FEMALE 1

#define INIT 0
#define ADDMEMBER 1
#define GETDISTANCE 2
#define COUNTMEMBER 3

#define COUPLE 0
#define PARENT 1
#define CHILD 2

#define NAME_LEN_MAX 19

////////////////////////////////////////////////////////////////////////////////

extern void init(char initialMemberName[], int initialMemberSex);
extern bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[]);
extern int getDistance(char nameA[], char nameB[]);
extern int countMember(char name[], int dist);

////////////////////////////////////////////////////////////////////////////////

static int score = 0;

static void cmd_init()
{
    char initialMemberName[NAME_LEN_MAX + 1];
    int initialMemberSex;

    scanf("%s %d", initialMemberName, &initialMemberSex);

    init(initialMemberName, initialMemberSex);
}

static void cmd_addMember()
{
    char newMemberName[NAME_LEN_MAX + 1];
    int newMemberSex;
    int relationship;
    char existingMemberName[NAME_LEN_MAX + 1];

    scanf("%s %d %d %s", newMemberName, &newMemberSex, &relationship, existingMemberName);

    bool userAns = addMember(newMemberName, newMemberSex, relationship, existingMemberName);

    int ans;
    scanf("%d", &ans);
    bool ansbool = ans == 1 ? true : false;

    if (ansbool != userAns)
    {
        score = 0;
    }
}

static void cmd_getDistance()
{
    char nameA[NAME_LEN_MAX + 1];
    char nameB[NAME_LEN_MAX + 1];

    scanf("%s %s", nameA, nameB);

    int userAns = getDistance(nameA, nameB);

    int ans;
    scanf("%d", &ans);

    if (ans != userAns)
    {
        score = 0;
    }
}

static void cmd_countMember()
{
    char name[NAME_LEN_MAX + 1];
    int dist;

    scanf("%s %d", name, &dist);

    int userAns = countMember(name, dist);

    int ans;
    scanf("%d", &ans);

    if (ans != userAns)
    {
        score = 0;
    }
}

int main()
{
    setbuf(stdout, NULL);

    //	freopen("sample_input.txt", "r", stdin);

    int T, scoreIdx;
    scanf("%d %d", &T, &scoreIdx);

    for (int TC = 1; TC <= T; TC++)
    {
        score = scoreIdx;

        int cmdL;
        scanf("%d", &cmdL);

        for (int cmdIdx = 0; cmdIdx < cmdL; ++cmdIdx)
        {
            int c_num;
            scanf("%d", &c_num);

            switch (c_num)
            {
            case INIT:
                cmd_init();
                break;

            case ADDMEMBER:
                cmd_addMember();
                break;

            case GETDISTANCE:
                cmd_getDistance();
                break;

            case COUNTMEMBER:
                cmd_countMember();
                break;

            default:
                break;
            }
        }

        printf("#%d %d\n", TC, score == scoreIdx ? scoreIdx : 0);
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////
#define Max_Num 200
#define couple 1
#define parent 2
#define child 3
typedef struct
{
    int front, rear;
    int items[Max_Num];
} Queue;

void InitQueue(Queue *pqueue);
int IsQFull(Queue *pqueue);
int IsQEmpty(Queue *pqueue);
int QPeek(Queue *pqueue);
void EnQueue(Queue *pqueue, int item);
int DeQueue(Queue *pqueue);

int mstrcmp(const char a[], const char b[]);
void mstrcpy(char dest[], const char src[]);
int mstrlen(const char a[]);

void addNew(char MemberName[], int MemberSex);
void addRelation(int idx, int relationship, char MemberName[], int MemberSex, int newMemberIdx);
int Where(const char a[], int len);
bool isPossible(int exstingMeberIdx, int newMemberSex, int relationship);
void isParent(int idx);
void isCouple(int idx);
void isChild(int idx);

typedef struct _GNode
{
    int Sex;
    char Name[20];
    int Name_len;
    struct _GNode *next;
} GNode;

typedef struct
{
    int num;
    GNode **heads;
} Graph;

Graph *pgraph;
int relation_map[Max_Num][Max_Num] = {0};
int sex_map[Max_Num][Max_Num] = {0};
int idx_map[Max_Num][Max_Num] = {0};
int isThere[Max_Num] = {0};

int test_n = 0;

void init(char initialMemberName[], int initialMemberSex)
{
    if (test_n != 0)
    {
        for (int i = 0; i < Max_Num; i++)
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
        for (int i = 0; i < pgraph->num; i++)
        {
            isThere[i] = 0;
            for (int j = 0; j < pgraph->num; j++)
            {
                relation_map[i][j] = 0;
                sex_map[i][j] = 0;
                idx_map[i][j] = 0;
            }
        }
    }

    pgraph->heads = (GNode **)malloc(sizeof(GNode *) * Max_Num);
    pgraph->num = 0;
    //GNode에 대한 포인터 배열
    //GNode에 대한 포인터 * 200의 크기를 가짐
    for (int i = 0; i < Max_Num; i++)
    {
        //num개의 더미노드 생성(헤드를 의미함)
        pgraph->heads[i] = (GNode *)malloc(sizeof(GNode));
        pgraph->heads[i]->next = NULL;
    }

    //노드 생성 후 0번째 더미노드에 연결
    addNew(initialMemberName, initialMemberSex);
    test_n++;
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[])
{
    int idx = Where(existingMemberName, mstrlen(newMemberName));
    int newMemberIdx = pgraph->num;
    if (!isPossible(idx, newMemberSex, relationship))
    {
        return false;
    }
    addNew(newMemberName, newMemberSex);
    addRelation(idx, relationship, newMemberName, newMemberSex, newMemberIdx);

    return true;
}

int getDistance(char nameA[], char nameB[])
{
    return -1;
}

int countMember(char name[], int dist)
{
    return -1;
}

//인덱스 값 반환
int Where(const char a[], int len)
{
    for (int i = 0; i < pgraph->num; i++)
    {
        GNode *cur = pgraph->heads[i]->next;
        if (cur->Name_len == len)
        {
            if (mstrcmp(cur->Name, a))
            {
                return i;
            }
        }
    }
    return 0;
}

bool isPossible(int exstingMeberIdx, int newMemberSex, int relationship)
{
    int relation_test;
    int exstingMemberSex = pgraph->heads[exstingMeberIdx]->next->Sex;

    //0: 관계 없음 1: 배우자 있음 2: 부모 있음 3: 자식 있음
    //0: 배우자 추가 1: 부모 추가 2: 자식 추가

    //자식 추가의 경우 예외 없음(2)
    if (relationship == 2)
    {
        return true;
    }
    //부모 추가의 경우(1)
    //부모만 고려(2)
    if (relationship == 1)
    {
        for (int i = 0; i < pgraph->num; i++)
        {
            relation_test = relation_map[exstingMeberIdx][i];
            //기존 부모가 없을 경우
            //relation_test가 0이면 이후 관계가 없음을 의미
            if (relation_test == 0)
            {
                return true;
            }
            //기존 부모가 있는데(2) 성별 또한 겹칠 경우
            if (relation_test == 2 && sex_map[exstingMeberIdx][i] == newMemberSex)
            {
                return false;
            }
        }
    }
    //배우자 추가의 경우(0)
    //배우자만 고려(1)
    else
    {
        //동성 결혼 금지
        if (exstingMemberSex == newMemberSex)
        {
            return false;
        }
        for (int i = 0; i < pgraph->num; i++)
        {
            relation_test = relation_map[exstingMeberIdx][i];
            //relation_test가 0이면 이후 관계가 없음을 의미
            if (relation_test == 0)
            {
                return true;
            }
            //배우자가 이미 있는 경우
            if (relation_test == 1)
            {
                return false;
            }
        }
    }
    return false;
}

void addNew(char MemberName[], int MemberSex)
{
    GNode *new, *cur;
    new = (GNode *)malloc(sizeof(GNode));
    mstrcpy(new->Name, MemberName);
    new->Name_len = mstrlen(MemberName);
    new->Sex = MemberSex;
    new->next = NULL;

    //num에 해당되는 더미노드를 선택하고 연결
    cur = pgraph->heads[pgraph->num++];
    cur->next = new;
}

//배우자(1), 부모(2), 자식(3)이 있으면 전역변수 리스트의 인덱스에 값 추가
//반복 종료 후 -1 추가
void isCouple(int idx)
{
    int t = 0;
    for (int i = 0; i < pgraph->num; i++)
    {
        isThere[i] = 0;
    }
    for (int i = 0; i < pgraph->num; i++)
    {
        if (relation_map[idx][i] == 0)
        {
            break;
        }
        if (relation_map[idx][i] == 1)
        {
            //실제 인덱스 값 (0~199)
            isThere[t] = idx_map[idx][i] - 1;
            t++;
        }
    }
    isThere[t] = -1;
}

void isParent(int idx)
{
    int t = 0;
    for (int i = 0; i < pgraph->num; i++)
    {
        isThere[i] = 0;
    }
    for (int i = 0; i < pgraph->num; i++)
    {
        if (relation_map[idx][i] == 0)
        {
            break;
        }
        if (relation_map[idx][i] == 2)
        {
            //실제 인덱스 값 (0~199)
            isThere[t] = idx_map[idx][i] - 1;
            t++;
        }
    }
    isThere[t] = -1;
}

void isChild(int idx)
{
    int t = 0;
    for (int i = 0; i < pgraph->num; i++)
    {
        isThere[i] = 0;
    }
    for (int i = 0; i < pgraph->num; i++)
    {
        if (relation_map[idx][i] == 0)
        {
            break;
        }
        if (relation_map[idx][i] == 3)
        {
            //실제 인덱스 값 (0~199)
            isThere[t] = idx_map[idx][i] - 1;
            t++;
        }
    }
    isThere[t] = -1;
}

void addRelation(int idx, int relationship, char MemberName[], int newMemberSex, int newMemberIdx)
{
    if (!isPossible(idx, newMemberSex, relationship))
    {
        return;
    }
    GNode *new, *cur;
    new = (GNode *)malloc(sizeof(GNode));
    mstrcpy(new->Name, MemberName);
    new->Name_len = mstrlen(MemberName);
    new->Sex = newMemberSex;
    new->next = NULL;

    int r = 0;
    //실제 노드 선택 후 반복에 따라 map에 추가
    cur = pgraph->heads[idx]->next;
    while (cur->next != NULL)
    {
        cur = cur->next;
        r++;
    }
    cur->next = new;
    relation_map[idx][r] = relationship;
    sex_map[idx][r] = newMemberSex;
    //0으로 초기화 되므로 +1 해줌
    idx_map[idx][r] = newMemberIdx + 1;

    //relationship에 따라 관계 추가 해야함
    //배우자 추가(0)의 경우 자식(3) 고려
    if (relationship == 0)
    {
        isChild(idx);
        int j = 0;
        while (isThere[j] != -1)
        {
        }
    }
    //부모 추가(1)의 경우
    else if (relationship == 1)
    {
    }
    //자식 추가의 경우 배우자 고려
    else
    {
    }
}
///////////////////////////

void InitQueue(Queue *pqueue)
{
    pqueue->front = pqueue->rear = 0;
}

int IsQFull(Queue *pqueue)
{
    return pqueue->front == (pqueue->rear + 1) % Max_Num;
}

int IsQEmpty(Queue *pqueue)
{
    return pqueue->front == pqueue->rear;
}

int QPeek(Queue *pqueue)
{
    if (IsQEmpty(pqueue))
        exit(1); //error: empty stack
    return pqueue->items[pqueue->front];
}

void EnQueue(Queue *pqueue, int item)
{
    if (IsQFull(pqueue))
        exit(1); //error: stack full
    pqueue->items[pqueue->rear] = item;
    pqueue->rear = (pqueue->rear + 1) % Max_Num;
}

int DeQueue(Queue *pqueue)
{
    if (IsQEmpty(pqueue))
        exit(1); //error: empty stack
    int item = pqueue->items[pqueue->front];
    pqueue->front = (pqueue->front + 1) % Max_Num;
    return item;
}

//동일하면 1, 다르면 0
int mstrcmp(const char a[], const char b[])
{
    int i;
    for (i = 0; a[i] != '\0'; ++i)
        if (a[i] != b[i])
            return 0;
    return 1;
}

void mstrcpy(char dest[], const char src[])
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

int mstrlen(const char a[])
{
    int i;
    for (i = 0; a[i] != '\0'; ++i)
        ;
    return i;
}