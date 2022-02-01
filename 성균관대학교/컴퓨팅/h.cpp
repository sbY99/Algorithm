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
///
///
///
///
#include <stdlib.h>

typedef struct item
{
    int num;
    int quantity;
    int price;
} Item;

typedef struct complete
{
    int price;
} Complete;

typedef struct data
{
    Item buy[5][100000];
    Item sell[5][100000];
    Complete profit[5][100000];
    int b[5];
    int s[5];
    int c[5];
} Data;

void toProfit(int price, int type);
void Check(Complete *best);

Data *stock;

int plz[5];
int best[5];

int test_n = 0;

typedef struct _where
{
    int is_buy;
    int type;
    int idx;
}Where;

Where where[100000];


void init()
{
    //첫 번쨰 테스트 케이스의 경우 free 불가능함
    if (test_n != 0)
    {
        free(stock);
    }
    //더미노드 생성
    stock = (Data *)malloc(sizeof(Data));
    for (int i = 0; i < 5; i++)
    {
        stock->b[i] = 0;
        stock->s[i] = 0;
        stock->c[i] = 0;
        plz[i]=1000000;
        best[i]=0;
    }
    test_n++;
}

int buy(int mNumber, int mStock, int mQuantity, int mPrice)
{
    Item *buying = stock->buy[mStock - 1];
    int realQ = mQuantity;
    //매도잔량 있는 경우
    //체결 가능한지 판단
    if (stock->s[mStock - 1] != 0)
    {
        Item *selling = stock->sell[mStock - 1];
        int i = 0;
        while (i < stock->s[mStock - 1])
        {
            //매수 체결을 위해서는 타입이 같고
            //매도잔량의 가격이 매수 값보다 작거나 같아야함
            if (selling[i].price <= mPrice)
            {
                if (realQ < selling[i].quantity)
                {
                    selling[i].quantity -= realQ;
                    toProfit(selling[i].price, mStock);
                    return 0;
                }
                else if (realQ == selling[i].quantity)
                {
                    toProfit(selling[i].price, mStock);
                    for (int j = i + 1; j < stock->s[mStock - 1]; j++)
                    {
                        selling[j - 1] = selling[j];
                        where[selling[j-1].num].idx--;
                    }
                    stock->s[mStock - 1]--;
                    return 0;
                }
                else if (realQ > selling[i].quantity)
                {
                    realQ -= selling[i].quantity;
                    toProfit(selling[i].price, mStock);
                    //삭제할 요소가 끝자리라면
                    //더 이상 체결 불가
                    if (i == stock->s[mStock - 1] - 1)
                    {
                        stock->s[mStock - 1]--;
                        Item temp;
                        temp.num = mNumber;
                        temp.price = mPrice;
                        temp.quantity = realQ;
                        int check = 0;
                        for (int t = 0; t < stock->b[mStock - 1]; t++)
                        {
                            if (buying[t].price < temp.price)
                            {
                                check++;
                                for (int k = stock->b[mStock - 1] - 1; k >= t; k--)
                                {
                                    buying[k + 1] = buying[k];
                                    where[buying[k+1].num].idx++;
                                }
                                where[buying[k+1].num].idx++;
                                b_here[mStock-1][mNumber]=t;
                                buying[t] = temp;
                                break;
                            }
                        }
                        if (check == 0)
                        {
                            b_here[mStock-1][mNumber]=stock->b[mStock-1];
                            buying[stock->b[mStock - 1]] = temp;
                        }
                        stock->b[mStock - 1]++;
                        return realQ;
                    }
                    for (int j = i + 1; j < stock->s[mStock - 1]; j++)
                    {
                        selling[j - 1] = selling[j];
                        s_here[mStock-1][selling[j-1].num]--;
                    }
                    stock->s[mStock - 1]--;
                    i--;
                }
            }
            i++;
        }
        //체결 안됨

        Item temp;
        temp.num = mNumber;
        temp.price = mPrice;
        temp.quantity = realQ;
        int check = 0;
        for (int t = 0; t < stock->b[mStock - 1]; t++)
        {
            if (buying[t].price < temp.price)
            {
                check++;
                for (int k = stock->b[mStock - 1] - 1; k >= t; k--)
                {
                    buying[k + 1] = buying[k];
                    b_here[mStock-1][buying[k+1].num]++;
                }
                b_here[mStock-1][mNumber]=t;
                buying[t] = temp;
                break;
            }
        }
        if (check == 0)
        {
            b_here[mStock-1][mNumber]=stock->b[mStock-1];
            buying[stock->b[mStock - 1]] = temp;
        }
        stock->b[mStock - 1]++;
        return realQ;
    }

    //매도잔량 없는 경우
    //단순히 매수 데이터 추가
    else
    {
        Item temp;
        temp.num = mNumber;
        temp.price = mPrice;
        temp.quantity = mQuantity;
        int check = 0;
        for (int t = 0; t < stock->b[mStock - 1]; t++)
        {
            if (buying[t].price < temp.price)
            {
                check++;
                for (int k = stock->b[mStock - 1] - 1; k >= t; k--)
                {
                    buying[k + 1] = buying[k];
                    b_here[mStock-1][buying[k+1].num]++;
                }
                b_here[mStock-1][mNumber]=t;
                buying[t] = temp;
                break;
            }
        }
        if (check == 0)
        {
            b_here[mStock-1][mNumber]=stock->b[mStock-1];
            buying[stock->b[mStock - 1]] = temp;
        }
        stock->b[mStock - 1]++;
        return mQuantity;
    }
}

int sell(int mNumber, int mStock, int mQuantity, int mPrice)
{
    Item *selling = stock->sell[mStock - 1];
    int realQ = mQuantity;
    //매수잔량 있는 경우
    //체결 가능한지 판단
    if (stock->b[mStock - 1] != 0)
    {
        Item *buying = stock->buy[mStock - 1];
        int i = 0;
        while (i < stock->b[mStock - 1])
        {
            //매도 체결을 위해서는 타입이 같고
            //매수잔량의 가격이 매도 값보다 크거나 같아야함
            if (buying[i].price >= mPrice)
            {
                if (realQ < buying[i].quantity)
                {
                    buying[i].quantity -= realQ;
                    toProfit(buying[i].price, mStock);
                    return 0;
                }
                else if (realQ == buying[i].quantity)
                {
                    toProfit(buying[i].price, mStock);
                    for (int j = i + 1; j < stock->b[mStock - 1]; j++)
                    {
                        buying[j - 1] = buying[j];
                        b_here[mStock-1][buying[j-1].num]--;
                        
                    }
                    stock->b[mStock - 1]--;
                    return 0;
                }
                else if (realQ > buying[i].quantity)
                {
                    realQ -= buying[i].quantity;
                    toProfit(buying[i].price, mStock);
                    //삭제할 요소가 끝자리라면
                    //더 이상 체결 불가
                    if (i == stock->b[mStock - 1] - 1)
                    {
                        stock->b[mStock - 1]--;
                        Item temp;
                        temp.num = mNumber;
                        temp.price = mPrice;
                        temp.quantity = realQ;
                        int check = 0;
                        for (int t = 0; t < stock->s[mStock - 1]; t++)
                        {
                            if (selling[t].price > temp.price)
                            {
                                check++;
                                for (int k = stock->s[mStock - 1] - 1; k >= t; k--)
                                {
                                    selling[k + 1] = selling[k];
                                    s_here[mStock-1][selling[k+1].num]++;
                                    
                                }
                                s_here[mStock-1][mNumber]=t;
                                selling[t] = temp;
                                break;
                            }
                        }
                        if (check == 0)
                        {
                            s_here[mStock-1][mNumber]=stock->s[mStock-1];
                            selling[stock->s[mStock - 1]] = temp;
                        }
                        stock->s[mStock - 1]++;
                        return realQ;
                    }
                    for (int j = i + 1; j < stock->b[mStock - 1]; j++)
                    {
                        buying[j - 1] = buying[j];
                        b_here[mStock-1][buying[j-1].num]--;
                        
                    }
                    stock->b[mStock - 1]--;
                    i--;
                }
            }
            i++;
        }

        Item temp;
        temp.num = mNumber;
        temp.price = mPrice;
        temp.quantity = realQ;
        int check = 0;
        for (int t = 0; t < stock->s[mStock - 1]; t++)
        {
            if (selling[t].price > temp.price)
            {
                check++;
                for (int k = stock->s[mStock - 1] - 1; k >= t; k--)
                {
                    selling[k + 1] = selling[k];
                    s_here[mStock-1][selling[k+1].num]++;
                }
                s_here[mStock-1][mNumber]=t;
                selling[t] = temp;
                break;
            }
        }
        if (check == 0)
        {
            s_here[mStock-1][mNumber]=stock->s[mStock-1];
            selling[stock->s[mStock - 1]] = temp;
        }
        stock->s[mStock - 1]++;
        return realQ;
    }

    //매수잔량 없는 경우
    //단순히 매도 데이터 추가
    else
    {
        Item temp;
        temp.num = mNumber;
        temp.price = mPrice;
        temp.quantity = mQuantity;
        int check = 0;
        for (int t = 0; t < stock->s[mStock - 1]; t++)
        {
            if (selling[t].price > temp.price)
            {
                check++;
                for (int k = stock->s[mStock - 1] - 1; k >= t; k--)
                {
                    selling[k + 1] = selling[k];
                    s_here[mStock-1][selling[k+1].num]++;
                }
                s_here[mStock-1][mNumber]=t;
                selling[t] = temp;
                break;
            }
        }
        if (check == 0)
        {
            s_here[mStock-1][mNumber]=stock->s[mStock-1];
            selling[stock->s[mStock - 1]] = temp;
        }
        stock->s[mStock - 1]++;
        return mQuantity;
    }
}
void cancel(int mNumber)
{
    
    for (int t = 0; t < 5; t++)
    {
        Item *cur = stock->buy[t];
        int idx= b_here[t][mNumber];
        if(cur[idx].num==mNumber){
            for(int i=idx+1;i<stock->b[t];i++){
                cur[i-1]=cur[i];
                b_here[t][cur[i-1].num]--;
            }
            b_here[t][mNumber]=0;
            stock->b[t]--;
            return;
        }
    }
    
    for (int t = 0; t < 5; t++)
    {
        Item *cur = stock->sell[t];
        int idx= s_here[t][mNumber];
        if(cur[idx].num==mNumber){
            for(int i=idx+1;i<stock->s[t];i++){
                cur[i-1]=cur[i];
                s_here[t][cur[i-1].num]--;
            }
            s_here[t][mNumber]=0;
            stock->s[t]--;
            return;
        }
    }
}

int bestProfit(int mStock)
{
    return best[mStock-1];
}

void toProfit(int price, int type)
{
    int min=plz[type-1];
    int b=best[type-1];
    Complete *pro=stock->profit[type-1];
    
    if(stock->c[type-1]==0){
        pro[0].price = price;
        stock->c[type-1]++;
        plz[type-1]=price;
        best[type-1]=0;
        return;
    }
    if(stock->c[type-1]==1){
        if(min>=price){
            plz[type-1]=price;
            pro[0].price = price;
            best[type-1]=0;
            return;
        }
        pro[1].price = price;
        stock->c[type-1]++;
        best[type-1]=price-pro[0].price;
        return;
    }
    else{
        if(min>=price){
            pro[stock->c[type-1]++].price=price;
            plz[type-1]=price;
            return;
        }
        if(price-min>b){
            best[type-1]=price-min;
            pro[stock->c[type-1]++].price=price;
            return;
        }
    }
}

