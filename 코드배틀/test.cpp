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
extern void arrest(int n);
extern void clearRoom();

void divide(int idx, int start, int end);

//start~end까지 범인이 있으면 1, 없으면 0
int Is_there(int idx, int start, int end)
{
    //0번째 방에 start~end까지 사람 넣음
    for (int i = start; i <= end; i++)
    {
        putIn(idx, i);
    }
    return closeDoor(idx);
}

void investigate()
{
    int idx = -1;
    for (int i = 0; i <= 900000; i += 100000)
    {
        divide(idx, i, i + 99999);
        clearRoom();
    }
}

void divide(int idx, int start, int end)
{
    int check = Is_there(++idx, start, end);
    if (check == 1)
    {
        if (end - start <= 10)
        {
            for (int i = start; i <= end; i++)
            {
                putIn(++idx, i);
                if (closeDoor(i) != 0)
                {
                    arrest(i);
                }
            }
            return;
        }
        int mid = (start + end) / 2;
        divide(idx, start, mid);
        divide(idx, mid + 1, end);
    }
}