//
//  test.c
//  3학년 1학기
//
//  Created by SB on 2021/09/28.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{false,true}bool;

typedef struct{
    int items[100];
    int top;
}Stack;

void InitStack(Stack *s){
    s->top=-1;
}

bool IsFull(Stack *s){
    return s->top == 99;
}

bool IsEmpty(Stack *s){
    return s->top==-1;
}

void push(Stack *s, int x){ /// x를 스택에 푸쉬하고 ptr 1증가
    if(IsFull(s))
        exit(1);
    s->items[++(s->top)]=x;
}

void pop(Stack *s){ /// 스택의 ptr을 감소시켜 사실상 없는 데이터로 만들음
    if(IsEmpty(s))
        exit(1);
    --(s->top);
}

char peek(Stack *s){ /// 스택의 꼭대기 값 반환
    if(IsEmpty(s))
        exit(1);
    return s->items[s->top];
}


bool Isdigit(char c){
    if('0'<=c&&c<='9'){
        return true;
    }
    else
        return false;
}


int GetPriority(char c){

    if(c=='+'||c=='-')
        return 1;
    if(c=='*'||c=='/')
        return 2;

    else
        return 0;
}

bool ComPrioirity(char c1,char c2){
    int n1=GetPriority(c1);
    int n2=GetPriority(c2);
    
    if(n1>=n2)
        return true;
    else
        return false;
}

void convert(char *exp, char *convExp, int n){ ///exp배열이 convExp배열로 바뀜
    Stack stack;
    int idx=0;
    InitStack(&stack);
    for(int i=0;i<n;i++){
        if(exp[i]=='('){
            push(&stack,exp[i]);
        }
        else if(exp[i]==')'){
            while(!IsEmpty(&stack)&&peek(&stack)!='('){
                convExp[idx++]=peek(&stack);
                pop(&stack);
            }
            pop(&stack);
        }
        
        else if(exp[i]>='0'&&exp[i]<='9'){
            convExp[idx++]=exp[i];
        }
        else{ ///만약 stack에 쌓인 연산자가 있으면 비교 실행, 없으면 그냥 저장
            while(!IsEmpty(&stack)&&ComPrioirity(peek(&stack),exp[i])){
                /// stack 맨 위의 연산자의 순위가 높거나 같으면 True 반환하여 반복문 실행
                /// stack 맨 위의 연산자를 출력하고 pop시킴
                convExp[idx++]=peek(&stack);
                pop(&stack);
            }
            push(&stack,exp[i]);
        }
    }
    while(!IsEmpty(&stack)){
        convExp[idx++]=peek(&stack);
        pop(&stack);
    }
}


int main(){
    char exp[100];
    char convExp[100];
    scanf("%s",exp);
    int n=strlen(exp);
    convert(exp,convExp,n);
    for(int i=0;i<n;i++){
        printf("%c",convExp[i]);
    }
    return 0;
}
