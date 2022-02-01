//
//  exercise3.c
//  3학년 1학기
//
//  Created by SB on 2021/10/19.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _Node
{
    int coef;
    int expon;
    struct _Node *next;
} Node;

typedef struct
{
    Node *tail;
    int len;
} Polynomial;

void Init_Node(Node *n, int co, int ex)
{
    n->coef = co;
    n->expon = ex;
    n->next = NULL;
}

void Init_Poly(Polynomial *p)
{
    p->tail = NULL;
    p->len = 0;
}

void insert(Polynomial *p, Node *n)
{
    if (p->len == 0)
    {
        p->tail = n;
        p->len++;
        return;
    }
    n->next = p->tail->next;
    // 맨 앞 노드와 맨 뒤 노드의 연결
    p->tail->next = n;
    // 원래 맨 뒤였던 노드의 next를 새로운 노드로 설정
    p->tail = n;
    //tail 최신화
    p->len++;
}

void multiply(Polynomial *r, Polynomial *a, Polynomial *b)
{
    Node *cur_a = a->tail->next;
    Node *cur_b = b->tail->next;
    int co;
    int ex;
    for (int i = 0; i < a->len; i++)
    {
        for (int j = 0; j < b->len; j++)
        {
            co = cur_a->coef * cur_b->coef;
            ex = cur_a->expon * cur_b->expon;
            if (r->len == 0)
            {
                Node *new = (Node *)malloc(sizeof(Node));
                Init_Node(new, co, ex);
                r->tail = new;
            }
            else
            {
                int temp = 0;
                Node *check = r->tail;
                for (int t = 0; t < r->len; t++)
                {
                    if (check->expon == ex)
                    {
                        check->coef = check->coef + co;
                        cur_b = cur_b->next;
                        temp = 1;
                        break;
                    }
                    check = check->next;
                }
                if (temp == 1)
                    continue;

                Node *new = (Node *)malloc(sizeof(Node));
                Init_Node(new, co, ex);
                r->tail = new;
            }
            r->len++;
            cur_b = cur_b->next;
        }

        cur_a = cur_a->next;
    }
}

int main()
{
    //다항식은 총 3개를 미리 선언해 놓고 Init 해놓음

    //반복문으로 사용자에게 coef, expon입력 받음
    //바로 노드 동적할당하고 Init 실행
    //parameter: (Node, coef, expon)
    //같은 for문 안에서 초기화된 노드를
    //순서에 맞는 다항식에 바로 대입
    //내림차순으로 입력받는 것을 가정
    //첫 다항식의 입력이 끝나면 두번째 다항식의 입력 실행

    //곱셈 호출

    return 0;
}
