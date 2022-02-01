//
//  2018313555_HW3A.c
//  3학년 1학기
//
//  Created by SB on 2021/11/01.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Modify from here */

/* Modify to here */

typedef enum
{
    false,
    true
} bool;

typedef struct _Node
{
    int octal;
    struct _Node *next;
} Node;

typedef struct
{
    Node *head;
    int len;
} LinkedList;

void InitList(LinkedList *plist);
int IsEmpty(LinkedList *plist);
void Insert(LinkedList *plist, int data);
void MergeTwoList(LinkedList *plist_a, LinkedList *plist_b, LinkedList *plist_c);
void PrintList(LinkedList *plist);
void PrintListHex(LinkedList *plist);

/* Modify from here */

/* Modify to here */

int main()
{
    int i, j;
    int cnt;
    int input;
    LinkedList list_a, list_b, list_c;

    InitList(&list_a);
    InitList(&list_b);
    InitList(&list_c);

    //리스트 두개 합병이므로 첫 번째에는 a 두 번째에는 b리스트에 입력
    for (i = 0; i < 2; i++)
    {
        //입력 받을 값의 개수
        scanf("%d", &cnt);
        for (j = 0; j < cnt; j++)
        {
            scanf("%d", &input);
            if (i == 0)
                Insert(&list_a, input);
            else
                Insert(&list_b, input);
        }
    }

    MergeTwoList(&list_a, &list_b, &list_c);

    PrintList(&list_a);
    PrintList(&list_b);
    PrintList(&list_c);
    PrintListHex(&list_c);

    return 0;
}

/* Modify from here */
void InitList(LinkedList *plist)
{
    //더미노드 생성
    plist->head = (Node *)malloc(sizeof(Node));
    plist->head->next = NULL;
    plist->len = 0;
}

int IsEmpty(LinkedList *plist)
{
    return plist->len == 0;
}

void Insert(LinkedList *plist, int data)
{
    Node *new = (Node *)malloc(sizeof(Node));
    new->next = NULL;
    new->octal = data;

    Node *cur = plist->head;

    for (int i = 0; i < plist->len; i++)
    {
        if (cur->next == NULL)
        {
            break;
        }
        //null 포인터의 참조를 막기 위함
        else if (data < cur->next->octal)
        {
            break;
        }
        //cur의 다음 노드의 값보다 작으면 멈춤
        //cur는 삽입할 위치의 이전에 있어야 하기 때문
        cur = cur->next;
    }
    new->next = cur->next;
    cur->next = new;

    plist->len++;
}

void MergeTwoList(LinkedList *plist_a, LinkedList *plist_b, LinkedList *plist_c)
{
    Node *cur_a = plist_a->head->next;
    Node *cur_b = plist_b->head->next;
    int len_a = plist_a->len;
    int len_b = plist_b->len;

    while (!IsEmpty(plist_a) && !IsEmpty(plist_b))
    {
        if (cur_a->octal < cur_b->octal)
        {
            Insert(plist_c, cur_a->octal);
            //새로운 노드와 배열을 생성해줌
            cur_a = cur_a->next;
            plist_a->len--;
        }
        else
        {
            Insert(plist_c, cur_b->octal);
            cur_b = cur_b->next;
            plist_b->len--;
        }
    }
    if (IsEmpty(plist_b))
    {
        while (!IsEmpty(plist_a))
        {
            Insert(plist_c, cur_a->octal);
            cur_a = cur_a->next;
            plist_a->len--;
        }
    }
    else if (IsEmpty(plist_a))
    {
        while (!IsEmpty(plist_b))
        {
            Insert(plist_c, cur_b->octal);
            cur_b = cur_b->next;
            plist_b->len--;
        }
    }

    plist_a->len = len_a;
    plist_b->len = len_b;
}

void PrintList(LinkedList *plist)
{
    for (Node *cur = plist->head->next; cur != NULL; cur = cur->next)
    {
        printf("%d ", cur->octal);
    }

    printf("\n");
}

void PrintListHex(LinkedList *plist)
{
    for (Node *cur = plist->head->next; cur != NULL; cur = cur->next)
    {
        int n = cur->octal;
        int dec = 0; //10진수로 변환
        int i = 1;

        if (n == 0)
        {
            printf("0 ");
            continue;
        }

        while (n != 0)
        {
            dec += (n % 10) * i;
            i *= 8;
            n /= 10;
        }
        char str[4];
        //16진수를 표현할 배열, 최대 3글자임
        //역순으로 출력하기 위해 배열 선언
        int j = 0;
        while (dec != 0)
        {
            int temp = dec % 16;
            if (temp >= 10)
            {
                str[j] = 'A' + temp - 10;
            }
            else
            {
                str[j] = '0' + temp;
            }
            dec /= 16;
            j++;
        }

        for (int k = 0; k < strlen(str); k++)
        {
            printf("%c", str[strlen(str) - k - 1]);
            //길이가 2이면 str[1], str[0] 순으로 붙어서 출력
        }
        //순서대로 저장 후 역순 출력
        printf(" ");
    }
    printf("\n");
}

/* Modify to here */
