#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_INPUT 10000
#define MAX_NUM 30000

extern void init();
extern void addUser(int uID, int income);
extern int getTop10(int result[10]);

static int input[MAX_INPUT];

static unsigned int seed = 13410;

static unsigned int pseudoRand()
{
    seed = seed * 214013 + 2531011;
    return (unsigned int)(seed >> 11) % MAX_NUM;
}

static void makeInput(int inputLen)
{
    for (int i = 0; i < inputLen; i++)
    {
        input[i] = pseudoRand();
    }
}

static int run()
{
    int N, userNum, uID = 0;
    int score = 100, result[10], cnt;
    int sum, check;
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &userNum);
        makeInput(userNum);
        for (int j = 0; j < userNum; j++)
        {
            addUser(uID++, input[j]);
        }
        cnt = getTop10(result);

        sum = 0;
        for (int j = 0; j < cnt; j++)
            sum += result[j];
        scanf("%d", &check);
        if (check != sum)
            score = 0;
    }
    return score;
}

int main(void)
{
    setbuf(stdout, NULL);
    //freopen("partial_sort_input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    for (int tc = 1; tc <= T; tc++)
    {
        init();
        printf("#%d %d\n", tc, run());
    }
    return 0;
}

// ----------------------Solution---------------------------

struct User
{
    int id;
    int income;
};

User user[100001];
int Cnt;

void init()
{
    Cnt = 0;
}

//인덱스 1부터 시작, 수입이 동일하면 ID작은 순으로 정렬
void addUser(int uID, int height)
{
    User newUser;
    newUser.id = uID;
    newUser.income = height;

    user[++Cnt] = newUser;
    int curr = Cnt;

    //부모가 없으면 종료
    while (curr / 2 >= 1)
    {
        int parent = curr / 2;

        //내림차순 정렬(수입 크면 우선순위 높음)
        if (user[parent].income > user[curr].income)
        {
            break;
        }
        //수입이 같은 경우 아이디가 작으면 우선순위 높음
        else if (user[parent].income == user[curr].income)
        {
            if (user[parent].id < user[curr].id)
            {
                break;
            }
        }
        //위 조건이 아니면 둘이 바꿈
        User temp = user[curr];
        user[curr] = user[parent];
        user[parent] = temp;

        curr = parent;
    }
}

int getChild(User *temp_user, int parent)
{
    int left = parent * 2;
    int right = parent * 2 + 1;

    if (temp_user[left].income > temp_user[right].income)
        return left;

    else if (temp_user[left].income < temp_user[right].income)
        return right;

    else
    {
        if (temp_user[left].id < temp_user[right].id)
            return left;
        return right;
    }
}

int Pop(User *temp_user)
{
    User last = temp_user[Cnt--];
    int r = temp_user[1].id;

    temp_user[1] = last;
    int curr = 1;

    //자식이 없으면 종료
    while (curr * 2 <= Cnt)
    {
        int child;

        //자식 노드가 하나 밖에 없음
        if (curr * 2 == Cnt)
        {
            child = Cnt;
        }
        else
        {
            child = getChild(temp_user, curr);
        }

        //우선 순위 정렬이 필요없으면 반복 종료
        if (temp_user[curr].income > temp_user[child].income)
            break;
        else if (temp_user[curr].income == temp_user[child].income)
        {
            if (temp_user[curr].id < temp_user[child].id)
                break;
        }

        User temp = temp_user[curr];
        temp_user[curr] = temp_user[child];
        temp_user[child] = temp;
        curr = child;
    }

    return r;
}

//10명 미만이면 수입 순으로 uID를 내림차순 정렬
//수입이 가장 큰 user 10명의 uID를 수입에 따라 내림차순 정렬
//result 개수 반환
int getTop10(int result[10])
{
    int count = Cnt;
    if (Cnt > 10)
    {
        count = 10;
    }

    User temp_user[100001];
    int temp_Cnt = Cnt;

    for (int i = 1; i <= Cnt; i++)
    {
        temp_user[i] = user[i];
    }

    for (int i = 0; i < count; i++)
    {
        result[i] = Pop(temp_user);
    }

    //Cnt 복구
    Cnt = temp_Cnt;

    return count;
}