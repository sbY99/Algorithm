#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 1
#define CMD_BUY 2
#define CMD_SELL 3
#define CMD_CANCEL 4
#define CMD_BEST_PROFIT 5

extern void init();
extern int buy(int mNumber, int mStock, int mQuantity, int mPrice);
extern int sell(int mNumber, int mStock, int mQuantity, int mPrice);
extern void cancel(int mNumber);
extern int bestProfit(int mStock);

typedef enum
{
    false,
    true
} bool;

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

static bool run()
{
    int numQuery;

    int mNumber, mStock, mQuantity, mPrice;

    int userAns, ans;

    bool isCorrect = false;

    scanf("%d", &numQuery);

    for (int i = 0; i < numQuery; ++i)
    {
        int cmd;
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            init();
            isCorrect = true;
            break;
        case CMD_BUY:
            scanf("%d %d %d %d", &mNumber, &mStock, &mQuantity, &mPrice);
            userAns = buy(mNumber, mStock, mQuantity, mPrice);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        case CMD_SELL:
            scanf("%d %d %d %d", &mNumber, &mStock, &mQuantity, &mPrice);
            userAns = sell(mNumber, mStock, mQuantity, mPrice);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        case CMD_CANCEL:
            scanf("%d", &mNumber);
            cancel(mNumber);
            break;
        case CMD_BEST_PROFIT:
            scanf("%d", &mStock);
            userAns = bestProfit(mStock);
            scanf("%d", &ans);
            if (userAns != ans)
            {
                isCorrect = false;
            }
            break;
        default:
            isCorrect = false;
            break;
        }
    }

    return isCorrect;
}

int main()
{
    setbuf(stdout, NULL);
    //freopen("sample_input.txt", "r", stdin);

    int T, MARK;
    scanf("%d %d", &T, &MARK);

    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    return 0;
}

/////////////////////////////////////////////
#include <stdlib.h>

typedef struct item
{
    int num;
    int quantity;
    int price;
    struct item *next;
} Item;

typedef struct complete
{
    int price;
    struct complete *next;
} Complete;

typedef struct data
{
    Item *buy[5];
    Item *sell[5];
    Complete *profit[5];
    int b[5];
    int s[5];
    int c[5];
} Data;

void toProfit(int price, int type);
void Check(Complete *best);

Data *stock;
int test_n = 0;

void init()
{
    //더미노드 생성
    stock = (Data *)malloc(sizeof(Data));
    for (int i = 0; i < 5; i++)
    {
        stock->buy[i] = (Item *)malloc(sizeof(Item));
        stock->sell[i] = (Item *)malloc(sizeof(Item));
        stock->profit[i] = (Complete *)malloc(sizeof(Complete));

        stock->buy[i]->next = NULL;
        stock->sell[i]->next = NULL;
        stock->profit[i]->next = NULL;

        stock->b[i] = 0;
        stock->s[i] = 0;
        stock->c[i] = 0;
    }
    test_n++;
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice)
{
    Item *buying = stock->buy[mStock - 1];
    Item *selling = stock->sell[mStock - 1];

    int realQ = mQuantity;
    //매도잔량 있는 경우
    //체결 가능한지 판단
    if (stock->s[mStock - 1] != 0)
    {
        while (selling->next != NULL)
        {
            Item *cur = selling;
            selling = selling->next;
            //매수 체결을 위해서는 타입이 같고
            //매도잔량의 가격이 매수 값보다 작거나 같아야함
            if (selling->price <= mPrice)
            {
                if (realQ < selling->quantity)
                {
                    selling->quantity -= realQ;
                    toProfit(selling->price, mStock);
                    return 0;
                }
                else if (realQ == selling->quantity)
                {
                    toProfit(selling->price, mStock);
                    cur->next = selling->next;
                    free(selling);
                    stock->s[mStock - 1]--;
                    return 0;
                }
                else if (realQ > selling->quantity)
                {
                    realQ -= selling->quantity;
                    toProfit(selling->price, mStock);
                    //삭제할 요소가 끝자리라면
                    //더 이상 체결 불가
                    if (selling->next == NULL)
                    {
                        cur->next = NULL;
                        free(selling);
                        stock->s[mStock - 1]--;
                        //처음
                        if (stock->b[mStock - 1] == 0)
                        {
                            Item *temp;
                            temp = (Item *)malloc(sizeof(Item));
                            temp->num = mNumber;
                            temp->price = mPrice;
                            temp->quantity = realQ;
                            temp->next = NULL;
                            buying->next = temp;
                            stock->b[mStock - 1]++;
                            return realQ;
                        }
                        //중간
                        while (buying->next != NULL)
                        {
                            if (buying->next->price < mPrice)
                            {
                                Item *temp;
                                temp = (Item *)malloc(sizeof(Item));
                                temp->num = mNumber;
                                temp->price = mPrice;
                                temp->quantity = realQ;
                                temp->next = buying->next;
                                buying->next = temp;
                                stock->b[mStock - 1]++;
                                return realQ;
                            }
                            buying = buying->next;
                        }
                        //끄
                        Item *temp;
                        temp = (Item *)malloc(sizeof(Item));
                        temp->num = mNumber;
                        temp->price = mPrice;
                        temp->quantity = realQ;
                        temp->next = NULL;
                        buying->next = temp;
                        stock->b[mStock - 1]++;
                        return realQ;
                    }

                    Item *temp;
                    temp = selling;
                    cur->next = selling->next;
                    selling = cur;
                    free(temp);
                    stock->s[mStock - 1]--;
                }
            }
        }
        //매도 잔량은 있으나 체결이 안됨
        //그냥 매수 데이터에 추가 해줌
        //처음
        buying = stock->buy[mStock - 1];
        if (stock->b[mStock - 1] == 0)
        {
            Item *temp;
            temp = (Item *)malloc(sizeof(Item));
            temp->num = mNumber;
            temp->price = mPrice;
            temp->quantity = realQ;
            temp->next = NULL;
            buying->next = temp;
            stock->b[mStock - 1]++;
            return realQ;
        }
        //중간
        while (buying->next != NULL)
        {
            if (buying->next->price < mPrice)
            {
                Item *temp;
                temp = (Item *)malloc(sizeof(Item));
                temp->num = mNumber;
                temp->price = mPrice;
                temp->quantity = realQ;
                temp->next = buying->next;
                buying->next = temp;
                stock->b[mStock - 1]++;
                return realQ;
            }
            buying = buying->next;
        }
        //끝
        Item *temp;
        temp = (Item *)malloc(sizeof(Item));
        temp->num = mNumber;
        temp->price = mPrice;
        temp->quantity = realQ;
        temp->next = NULL;
        buying->next = temp;
        stock->b[mStock - 1]++;
        return realQ;
    }

    //매도잔량 없는 경우
    //단순히 매수 데이터 추가
    else
    {
        //처음
        if (stock->b[mStock - 1] == 0)
        {
            Item *temp;
            temp = (Item *)malloc(sizeof(Item));
            temp->num = mNumber;
            temp->price = mPrice;
            temp->quantity = mQuantity;
            temp->next = NULL;
            buying->next = temp;
            stock->b[mStock - 1]++;
            return mQuantity;
        }
        //중간
        while (buying->next != NULL)
        {
            if (buying->next->price < mPrice)
            {
                Item *temp;
                temp = (Item *)malloc(sizeof(Item));
                temp->num = mNumber;
                temp->price = mPrice;
                temp->quantity = mQuantity;
                temp->next = buying->next;
                buying->next = temp;
                stock->b[mStock - 1]++;
                return mQuantity;
            }
            buying = buying->next;
        }
        //끝
        Item *temp;
        temp = (Item *)malloc(sizeof(Item));
        temp->num = mNumber;
        temp->price = mPrice;
        temp->quantity = mQuantity;
        temp->next = NULL;
        buying->next = temp;
        stock->b[mStock - 1]++;
        return mQuantity;
    }
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
    Item *selling = stock->sell[mStock - 1];
    Item *buying = stock->buy[mStock - 1];
    int realQ = mQuantity;
    //매수잔량 있는 경우
    //체결 가능한지 판단
    if (stock->b[mStock - 1] != 0)
    {

        while (buying->next != NULL)
        {
            Item *cur = buying;
            buying = buying->next;

            //매도 체결을 위해서는 타입이 같고
            //매수잔량의 가격이 매도 값보다 크거나 같아야함
            if (buying->price >= mPrice)
            {
                if (realQ < buying->quantity)
                {
                    buying->quantity -= realQ;
                    toProfit(buying->price, mStock);
                    return 0;
                }
                else if (realQ == buying->quantity)
                {
                    toProfit(buying->price, mStock);
                    cur->next = buying->next;
                    free(buying);
                    stock->b[mStock - 1]--;
                    return 0;
                }
                else if (realQ > buying->quantity)
                {
                    realQ -= buying->quantity;

                    toProfit(buying->price, mStock);
                    //삭제할 요소가 끝자리라면
                    //더 이상 체결 불가
                    if (buying->next == NULL)
                    {
                        cur->next = NULL;
                        free(buying);
                        stock->b[mStock - 1]--;
                        //처음
                        if (stock->s[mStock - 1] == 0)
                        {
                            Item *temp;
                            temp = (Item *)malloc(sizeof(Item));
                            temp->num = mNumber;
                            temp->price = mPrice;
                            temp->quantity = realQ;
                            temp->next = NULL;
                            selling->next = temp;
                            stock->s[mStock - 1]++;
                            return realQ;
                        }
                        //중간
                        while (selling->next != NULL)
                        {
                            if (selling->next->price > mPrice)
                            {
                                Item *temp;
                                temp = (Item *)malloc(sizeof(Item));
                                temp->num = mNumber;
                                temp->price = mPrice;
                                temp->quantity = realQ;
                                temp->next = selling->next;
                                selling->next = temp;
                                stock->s[mStock - 1]++;
                                return realQ;
                            }
                            selling = selling->next;
                        }
                        //끝
                        Item *temp;
                        temp = (Item *)malloc(sizeof(Item));
                        temp->num = mNumber;
                        temp->price = mPrice;
                        temp->quantity = realQ;
                        temp->next = NULL;
                        selling->next = temp;
                        stock->s[mStock - 1]++;
                        return realQ;
                    }
                    //끝자리가 아니면 해당 노드 삭제 후
                    //다시 반복문 시작
                    Item *temp;
                    temp = buying;
                    cur->next = buying->next;
                    buying = cur;
                    free(temp);
                    stock->b[mStock - 1]--;
                }
            }
        }
        //체결 불가능
        //처음
        selling = stock->sell[mStock - 1];
        if (stock->s[mStock - 1] == 0)
        {
            Item *temp;
            temp = (Item *)malloc(sizeof(Item));
            temp->num = mNumber;
            temp->price = mPrice;
            temp->quantity = realQ;
            temp->next = NULL;
            selling->next = temp;
            stock->s[mStock - 1]++;
            return realQ;
        }
        while (selling->next != NULL)
        {
            if (selling->next->price > mPrice)
            {
                Item *temp;
                temp = (Item *)malloc(sizeof(Item));
                temp->num = mNumber;
                temp->price = mPrice;
                temp->quantity = realQ;
                temp->next = selling->next;
                selling->next = temp;
                stock->s[mStock - 1]++;
                return realQ;
            }
            selling = selling->next;
        }
        //끝
        Item *temp;
        temp = (Item *)malloc(sizeof(Item));
        temp->num = mNumber;
        temp->price = mPrice;
        temp->quantity = realQ;
        temp->next = NULL;
        selling->next = temp;
        stock->s[mStock - 1]++;
        return realQ;
    }

    //매수잔량 없는 경우
    //단순히 매도 데이터 추가
    else
    {
        //처음
        if (stock->s[mStock - 1] == 0)
        {
            Item *temp;
            temp = (Item *)malloc(sizeof(Item));
            temp->num = mNumber;
            temp->price = mPrice;
            temp->quantity = mQuantity;
            temp->next = NULL;
            selling->next = temp;
            stock->s[mStock - 1]++;
            return realQ;
        }
        //중간
        while (selling->next != NULL)
        {
            if (selling->next->price > mPrice)
            {
                Item *temp;
                temp = (Item *)malloc(sizeof(Item));
                temp->num = mNumber;
                temp->price = mPrice;
                temp->quantity = mQuantity;
                temp->next = selling->next;
                selling->next = temp;
                stock->s[mStock - 1]++;
                return mQuantity;
            }
            selling = selling->next;
        }
        //끝
        Item *temp;
        temp = (Item *)malloc(sizeof(Item));
        temp->num = mNumber;
        temp->price = mPrice;
        temp->quantity = mQuantity;
        temp->next = NULL;
        selling->next = temp;
        stock->s[mStock - 1]++;
        return mQuantity;
    }
}

void cancel(int mNumber)
{
    for (int t = 0; t < 5; t++)
    {
        Item *cur = stock->buy[t];
        if (stock->b[t] == 0)
        {
            continue;
        }
        while (cur->next != NULL)
        {
            if (cur->next->num == mNumber)
            {
                Item *temp;
                temp = cur->next;
                cur->next = temp->next;
                free(temp);
                stock->b[t]--;
                return;
            }
            cur = cur->next;
        }
    }
    for (int t = 0; t < 5; t++)
    {
        Item *cur = stock->sell[t];
        if (stock->s[t] == 0)
        {
            continue;
        }
        while (cur->next != NULL)
        {
            if (cur->next->num == mNumber)
            {
                Item *temp;
                temp = cur->next;
                cur->next = temp->next;
                free(temp);
                stock->s[t]--;
                return;
            }
            cur = cur->next;
        }
    }
}

int bestProfit(int mStock)
{
    int max = 0;
    Complete *best = stock->profit[mStock - 1];
    for (int i = 0; i < stock->c[mStock - 1] - 1; i++)
    {
        for (int j = i + 1; j < stock->c[mStock - 1]; j++)
        {
            if (best[j].price - best[i].price > max)
            {
                max = best[j].price - best[i].price;
            }
        }
    }
    return max;
}

void toProfit(int price, int type)
{
    stock->profit[type - 1][stock->c[type - 1]].price = price;
    stock->c[type - 1]++;
}
