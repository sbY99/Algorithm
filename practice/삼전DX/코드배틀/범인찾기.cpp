// Title : 범인 색출, Score 를 최소화하라
// 20 초
// stack Memory : 1M  (전역 변수 사용 금지)

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <time.h>
#include <random>

extern void investigate();

const int MAX_NUM = 1000000;
static int SCORE, TOTAL_SCORE, TOTAL_TIME;
static char citizen[MAX_NUM];
static char room[MAX_NUM];
static char arrested[MAX_NUM];

void putIn(int n, int a)
{
    if (n < 0 || n >= MAX_NUM)
        return;
    if (a < 0 || a >= MAX_NUM)
        return;
    room[n] |= citizen[a];
}

int closeDoor(int n)
{
    SCORE += 1;
    if (n < 0 || n >= MAX_NUM)
        return 0;
    return room[n];
}

void clearRoom()
{
    for (int i = 0; i < MAX_NUM; i++)
        room[i] = 0;
}

void arrest(int a)
{
    SCORE += 10;
    if (a < 0 || a >= MAX_NUM)
        return;
    if (citizen[a] == 0)
        SCORE += 10000;
    arrested[a] = 1;
}

static unsigned long long seed = 113;
std::random_device rd;
std::mt19937 gen(seed);
std::uniform_int_distribution<int> dis(0, MAX_NUM - 1);

void init()
{
    SCORE = 0;
    for (int i = 0; i < MAX_NUM; i++)
    {
        citizen[i] = 0;
        room[i] = 0;
        arrested[i] = 0;
    }
    int j;
    for (int i = 0; i < MAX_NUM / 1000; i++)
    {
        j = dis(gen);
        if (citizen[j] == 1)
        {
            i--;
            continue;
        }
        citizen[j] = 1;
    }
}

int main()
{
    int TC;
    TOTAL_SCORE = TOTAL_TIME = 0;
    //freopen("sample_input.txt", "r", stdin);
    scanf("%d", &TC);
    for (int t = 1; t <= TC; t++)
    {
        init();
        investigate();
        for (int i = 0; i < MAX_NUM; i++)
            if (citizen[i] == 1 && arrested[i] == 0)
                SCORE += 90000;
        if (SCORE < 86400)
            printf("#%d 100 %d\n", t, SCORE);
        else
            printf("#%d 0 0\n", t);
        TOTAL_SCORE += SCORE;
    }
    printf("TOTAL SCORE : %d\n", TOTAL_SCORE);
}

//////////////---------------------//////////////////////////
extern void putIn(int n, int a);
extern int closeDoor(int n);
extern void arrest(int a);
extern void clearRoom();

void solve(int l, int r, int &cNum, int &rNum)
{
    if (r == l)
    {
        arrest(r);
        cNum--;
        return;
    }
    int m = (l + r) / 2;
    bool t = 0;

    //반으로 나눈 후,
    //중간부터 오른쪽 까지 검사했을때 범인이 있다면
    for (int i = m + 1; i <= r; i++)
        putIn(rNum, i);
    if (t = closeDoor(rNum++))
        solve(m + 1, r, cNum, rNum);

    //범인을 모두 잡은 경우 리턴
    if (cNum == 0)
        return;

    //오른쪽에 범인이 없다면
    //왼쪽에는 무조건 범인이 있으므로 검사하지 않고 재귀호출
    if (!t)
        solve(l, m, cNum, rNum);
    //오른쪽에 범인이 있다면
    //왼쪽도 범인 있을 수 있으므로 검사 후 재귀 호출
    else
    {
        for (int i = l; i <= m; i++)
            putIn(rNum, i);
        if (closeDoor(rNum++))
            solve(l, m, cNum, rNum);
    }
}

void investigate()
{

    int cNum = 1000, rNum = 0;
    solve(0, 999999, cNum, rNum);
}