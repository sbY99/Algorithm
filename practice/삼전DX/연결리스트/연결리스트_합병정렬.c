#include <stdio.h>
#include <stdlib.h>

typedef struct _node
{
    int data;
    struct _node *link;
} NODE;

//병합
NODE *Merge(NODE *left, NODE *right)
{
    NODE *node = (NODE *)malloc(sizeof(NODE)); //임시head 생성
    NODE *head = node;
    while (left && right)
    { //왼쪽리스트와오른쪽리스트중현재값이더작은값을node에붙인다.
        if (left->data < right->data)
        {
            node->link = left;
            left = left->link;
            node = node->link;
        }
        else
        {
            node->link = right;
            right = right->link;
            node = node->link;
        }
    } //남아있는리스트를뒤에만들어진노드뒤에붙인다.
    if (left)
    {
        node->link = left;
    }
    else
    {
        node->link = right;
    }
    node = head->link; //임시head 제거
    free(head);
    return node;
} //분할
NODE *Devide(NODE *first, int size)
{
    int i;
    NODE *left = first;
    NODE *right = first;
    NODE *prev_right = first; //리스트중가운데원소를찾는다.
    for (i = 0; i < (size / 2) - 1; i++)
    {
        prev_right = prev_right->link;
    }
    right = prev_right->link;
    //왼쪽의마지막원소의link를아무것도가리키지않는상태로바꾼다.
    prev_right->link = NULL;
    //원소의크기가1이상일경우에대해분할을다시한다.
    if (size / 2 > 1)
        left = Devide(left, size / 2);
    if (size - (size / 2) > 1)
        right = Devide(right, size - (size / 2));
    //왼쪽과오른쪽을합친값을return한다.
    returnMerge(left, right);
}
voidMergeSort(int data[], int size)
{
    int i;
    //정렬되지않은집합(head)에기존데이터를대입한다.
    NODE *head_unsorted = (NODE *)malloc(sizeof(NODE)); //정렬되지않은집합생성(head)
    NODE *node = head_unsorted;
    head_unsorted->link = NULL;
    for (i = 0; i < size; i++)
    {
        node->link = (NODE *)malloc(sizeof(NODE));
        node = node->link;
        node->data = data[i];
        node->link = NULL;
    }
    //병합정렬시작
    node = Devide(head_unsorted->link, size);
    free(head_unsorted);
    for (i = 0; i < size; i++)
    {
        data[i] = node->data;
        node = node->link;
    }
    return;
}
int main()
{
    int data[1000], i;
    for (i = 0; i < 1000; i++)
    {
        data[i] = rand() % 1000;
    }
    MergeSort(data, 1000);
    for (i = 0; i < 999; i++)
    {
        if (data[i] > data[i + 1])
        {
            puts("Error");
            break;
        }
    }
    return 0;
}
