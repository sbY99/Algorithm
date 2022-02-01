//
//  2018313555_HW2B.c
//  3학년 1학기
//
//  Created by SB on 2021/10/03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef enum {false, true} bool;

typedef struct STACK
{
    char data[MAX_SIZE];
    int top; // 스택의 top에 대한 인덱스

}STACK;


void InitStack(STACK *p)
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
        return ;
    }
    else
    {
        p->data[++(p->top)]=data;
    }
}

int Pop(STACK *p)
{
    if(Is_empty(p))
        return -1;
    
    return p->data[(p->top)--];
}

int Peek(STACK *p)
{
    if(Is_empty(p))
        return -1;
     
    return p->data[p->top];
}

int main(){
    STACK s;
    InitStack(&s);
    int check=0;
    char in[100];
    scanf("%s",in);
    int n=strlen(in);
    for(int i=0;i<n;i++){
        Push(&s,in[i]);
    }
    for(int i=0;i<n;i++){
        char ch=Peek(&s);
        printf("%c",ch);
        if(in[i]!=ch){
            if(in[i]!='*'&&ch!='*'){
                check++;
            }
        }
        Pop(&s);
    }
    printf("\n%d",check);
    return 0;
}
