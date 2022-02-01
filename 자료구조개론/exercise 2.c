//
//  ee.c
//  3학년 1학기
//
//  Created by SB on 2021/09/24.
//

#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct STACK
{
    char data[MAX_SIZE];
    int top; // 스택의 top에 대한 인덱스

}STACK;


void Init(STACK *p)
{
    p->top=-1;
}

int Is_empty(STACK *p)
{
    return (p->top == -1);
}

int Is_full(STACK *p)
{
    return (p->top == (MAX_SIZE-1));
}

void Push(STACK *p,char data)
{
    if(Is_full(p))
    {
        printf("스택이 꽉찼습니다\n"); return ;
    }
    else
    {
        p->data[++(p->top)]=data;
    }
}

int Pop(STACK *p)
{
    if(Is_empty(p))
    {
        printf("스택이 비어있습니다\n");
        return -1;
    }
     
    return p->data[(p->top)--];
}

int Peek(STACK *p)
{
    if(Is_empty(p))
    {
        printf("스택이 비어있습니다\n");
        return -1;
    }
     
    return p->data[p->top];
}

int ComPrioirity(char op) // 연산자의 우선순위 반환 함수
{
    switch(op)
    {
        case '(' : case ')' : return 0;
        case '+' : case '-' : return 1;
        case '*' : case '/' : return 2;
    }
     
    return -1;
}

int InfixToPostfix(char *exp) // 후위표기식으로 식을 변경하는 함수
{
    STACK s;
    char ch,top_op;
    int i,len=strlen(exp);
     
    Init(&s);

    for(i=0;i<len;i++)
    {
        ch=exp[i];

        switch(ch)
        {
            case '+' :    case '-' :    case '*' :    case '/' : //우선순위에 따라 저장
                while(!Is_empty(&s) && ComPrioirity(ch) <= ComPrioirity(Peek(&s)))
                    printf("%c",Pop(&s));
                 
                Push(&s,ch);
                break;

            case '(' : // (는 무조건 스택에 저장
                Push(&s,ch);
                break;

            case ')' : // )를 입력받으면 이전의 (를 찾을때 까지 쌓여있는 연산자를 출력함
                top_op=Pop(&s);

                while(top_op != '(')
                {
                    printf("%c",top_op);
                    top_op=Pop(&s);
                }
                break;

            default : // 연산자가 아니면 그냥 바로 출력
                printf("%c",ch);
                break;
        }
    }

    while(!Is_empty(&s))
        printf("%c",Pop(&s));

    return 0;
}

int Eval(char *exp) // 후위표기식을 계산하는 함수
{
    STACK s;
    int i,len=strlen(exp);
    char ch;
    int a,b;

    Init(&s);

    for(i=0;i<len;i++)
    {
        ch=exp[i];
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/')
            Push(&s,ch-'0'); // 피연산자
        else
        {
            b=Pop(&s);
            a=Pop(&s);

            switch(ch)
            {
                case '+' :    Push(&s,a+b);    break;
                case '-' :    Push(&s,a-b);    break;
                case '*' :    Push(&s,a*b);    break;
                case '/' :    Push(&s,a/b);    break;
            }
        }
    }

    return Pop(&s);
}

int main()
{
    char string[50];

    printf("수식 입력 : ");
    printf("후위표기식 출력 : ",gets(string));
    InfixToPostfix(string);
    puts("\n-------------------------------------");
    printf("계산 수식 입력(후위표기식으로 입력) : ");
    printf("후위표기식 계산 결과: %d\n",Eval(gets(string)));
     
    return 0;
}
