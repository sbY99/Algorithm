#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STACK 100

typedef enum {false , true} bool;

typedef struct {
    char small;
    char large;
    // *Variable "operator"
    // used in ConvInfixToPostfix function
    char operator;
}Hexa_num;

typedef struct {
    Hexa_num items[MAX_STACK];
    int top;
}Stack;

/* Modify from here */
bool ComPrioirity(char c1,char c2);
int GetPriority(char c);
bool Isdigit(char c);
/* Modify to here */

Hexa_num add(Hexa_num b1,Hexa_num b2);
Hexa_num subtract(Hexa_num b1,Hexa_num b2);
Hexa_num multiply(Hexa_num b1,Hexa_num b2);
Hexa_num division(Hexa_num b1,Hexa_num b2);

void InitStack (Stack *pstack);
bool IsFull(Stack *pstack);
bool IsEmpty(Stack *pstack);
Hexa_num Peek(Stack *pstack);
void Push(Stack *pstack,Hexa_num item);
void Pop(Stack *pstack);
void ConvInfixToPostfix(char* exp,char* convExp, int len);
Hexa_num EvalPostfix(char* exp,int len);
void print_Hexa_num(Hexa_num result);



int main() {
    char infix_exp[100];
    char postfix_exp[100];
    Hexa_num result;
    scanf("%s",infix_exp);
    ConvInfixToPostfix(infix_exp,postfix_exp,strlen(infix_exp));
    printf("%s\n",postfix_exp);
    result = EvalPostfix(postfix_exp,strlen(postfix_exp));
    
    print_Hexa_num(result);
    
    return 0;
}
/* Modify from here */
void InitStack(Stack *s){
    s->top=-1; //(스택의 개수-1)이자 (꼭대기 값의 인덱스)를 의미, 값 추가될 때 마다 1씩 증가
}
bool IsFull(Stack *s){
    if(s->top>=MAX_STACK-1)
        return true;
    else
        return false;
}

bool IsEmpty(Stack *s){
    if(s->top<=-1)
        return true;
    else
        return false;
}

Hexa_num Peek(Stack *s){
    return s->items[s->top];
}

void Push(Stack *s, Hexa_num item){
    s->top++;
    s->items[s->top]=item; //top의 인덱스를 증가시킨 뒤 아이템을 입력
}

void Pop(Stack *s){
    s->top--; //top의 값 감소
}

void ConvInfixToPostfix(char *exp, char *convExp, int len){
    Stack s;
    InitStack(&s);
    int idx=0;
    for(int i=0;i<len;i++){
        if(Isdigit(exp[i])){
            convExp[idx++]=exp[i];
        }
        else{ ///만약 stack에 쌓인 연산자가 있으면 비교 실행, 없으면 그냥 저장
            if(!IsEmpty(&s)){
                Hexa_num compare=Peek(&s);
                while(!IsEmpty(&s)&&ComPrioirity(compare.operator,exp[i])){
                    /// stack 맨 위의 연산자의 순위가 높거나 같으면 True 반환하여 반복문 실행
                    /// stack 맨 위의 연산자를 출력하고 pop시킴
                    convExp[idx++]=compare.operator;
                    Pop(&s);
                    compare=Peek(&s);
                }
            }
            Hexa_num put;
            put.operator=exp[i];
            Push(&s,put);
        }
    }
    while(!IsEmpty(&s)){
        Hexa_num item =Peek(&s);
        convExp[idx++]=item.operator;
        Pop(&s);
    }
    convExp[idx]='\0';
}



int GetPriority(char c){
    if(c=='+'||c=='-')
        return 1;
    if(c=='*'||c=='/')
        return 2;
    else
        return -1;
}

bool ComPrioirity(char c1,char c2){
    int n1=GetPriority(c1);
    int n2=GetPriority(c2);
    
    if(n1>=n2)
        return true;
    else
        return false;
}

bool Isdigit(char c){
    if(('0'<=c&&c<='9')||('A'<=c&&c<='F'))
        return true;
    
    else
        return false;
}

Hexa_num add(Hexa_num b1,Hexa_num b2){
    Hexa_num n;
    int a=0,b=0;
    if(b1.large>='A')
        a+=(b1.large-'A'+10)*16;
    else
        a+=(b1.large-'0')*16;
    if(b1.small>='A')
       a+=b1.small-'A'+10;
    else
       a+=b1.small-'0';
    if(b2.large>='A')
        b+=(b2.large-'A'+10)*16;
    else
        b+=(b2.large-'0')*16;
    if(b2.small>='A')
       b+=b2.small-'A'+10;
    else
       b+=b2.small-'0';//b1, b2의 10진수 변환 = a,b
    int c=a+b;
    int big=c/16,sm=c%16;
    if(big>=10){
        n.large='A'+(big-10);
    }
    else{
        n.large=48+big;
    }
    if(sm>10){
        n.small='A'+(sm-10);
    }
    else{
        n.small=48+sm;
    }
    return n;
}
Hexa_num subtract(Hexa_num b1,Hexa_num b2){
    Hexa_num n;
    int a=0,b=0;
    if(b1.large>='A')
        a+=(b1.large-'A'+10)*16;
    else
        a+=(b1.large-'0')*16;
    if(b1.small>='A')
       a+=b1.small-'A'+10;
    else
       a+=b1.small-'0';
    if(b2.large>='A')
        b+=(b2.large-'A'+10)*16;
    else
        b+=(b2.large-'0')*16;
    if(b2.small>='A')
       b+=b2.small-'A'+10;
    else
       b+=b2.small-'0'; //b1, b2의 10진수 변환 = a,b
    int c=a-b;
    int big=c/16,sm=c%16;
    if(big>=10){
        n.large='A'+(big-10);
    }
    else{
        n.large=48+big;
    }
    if(sm>10){
        n.small='A'+(sm-10);
    }
    else{
        n.small=48+sm;
    }
    return n;
}
Hexa_num multiply(Hexa_num b1,Hexa_num b2){
    Hexa_num n;
    int a=0,b=0;
    if(b1.large>='A')
        a+=(b1.large-'A'+10)*16;
    else
        a+=(b1.large-'0')*16;
    if(b1.small>='A')
       a+=b1.small-'A'+10;
    else
       a+=b1.small-'0';
    if(b2.large>='A'){
        
        b+=(b2.large-'A'+10)*16;
    }
    else{
        b+=(b2.large-'0')*16;
    }
    if(b2.small>='A')
       b+=b2.small-'A'+10;
    else
       b+=b2.small-'0'; //b1, b2의 10진수 변환 = a,b
    int c=a*b;
    int big=c/16,sm=c%16;
    if(big>=10){
        n.large='A'+(big-10);
    }
    else{
        n.large=48+big;
    }
    
    if(sm>10){
        n.small='A'+(sm-10);
    }
    else{
        n.small=48+sm;
    }
    return n;
}
Hexa_num division(Hexa_num b1,Hexa_num b2){
    Hexa_num n;
    int a=0,b=0;
    if(b1.large>='A')
        a+=(b1.large-'A'+10)*16;
    else
        a+=(b1.large-'0')*16;
    if(b1.small>='A')
       a+=b1.small-'A'+10;
    else
       a+=b1.small-'0';
    if(b2.large>='A')
        b+=(b2.large-'A'+10)*16;
    else
        b+=(b2.large-'0')*16;
    if(b2.small>='A')
       b+=b2.small-'A'+10;
    else
       b+=b2.small-'0'; //b1, b2의 10진수 변환 = a,b
    int c=a/b;
    int big=c/16,sm=c%16;
    if(big>=10){
        n.large='A'+(big-10);
    }
    else{
        n.large=48+big;
    }
    if(sm>10){
        n.small='A'+(sm-10);
    }
    else{
        n.small=48+sm;
    }
    return n;
}

Hexa_num EvalPostfix(char* exp,int len){
    Stack e_s;
    InitStack(&e_s);
    for(int i=0;i<len;i++){
        Hexa_num re;
        if(Isdigit(exp[i])){
            Hexa_num num;
            num.large=exp[i++];
            num.small=exp[i];
            Push((&e_s),num);
        }
        else{
            Hexa_num peek1=Peek(&e_s);
            Pop(&e_s);
            Hexa_num peek2=Peek(&e_s);
            Pop(&e_s);
            switch(exp[i]){
                case '+':
                    re=add(peek2,peek1);
                    Push(&e_s,re);
                    break;
                case '-':
                    re=subtract(peek2,peek1);
                    Push(&e_s,re);
                    break;
                case '*':
                    re=multiply(peek2,peek1);
                    Push(&e_s,re);
                    break;
                case '/':
                    re=division(peek2,peek1);
                    Push(&e_s,re);
                    break;
            }
        }
    }
    
    return Peek(&e_s);
}

void print_Hexa_num(Hexa_num result){
    printf("%c%c",result.large,result.small);
}
/* Modify to here */
