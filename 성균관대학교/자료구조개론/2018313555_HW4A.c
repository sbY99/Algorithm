//
//  2018313555_HW4A.c
//  3학년 1학기
//
//  Created by SB on 2021/11/11.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Modify from here */

/* Modify to here */

#define MAX_HEAP 100

typedef enum
{
    false,
    true
} bool;

typedef struct
{
    char small;
    char middle;
    char large;
} Hexa_num;

typedef struct
{
    Hexa_num data;
    // This is a priority as well as data
} PNode;

typedef struct
{
    PNode items[MAX_HEAP + 1];
    int num;
} Heap;

void InitHeap(Heap *pheap);

bool IsEmpty(Heap *pheap);

bool IsFull(Heap *pheap);

void Insert(Heap *pheap, Hexa_num data);

Hexa_num Delete(Heap *pheap);

void HeapSort(Hexa_num a[], int n);

Hexa_num *CreateHexaNum(int n);

void GetInput();

/* Modify from here */

int GetParent(int idx);

int GetLeftChild(int idx);

int GetRightChild(int idx);

int GetHighPrioityChild(Heap *pheap, int idx);

/* Modify to here */

int main()
{

    GetInput();
    /*
    5
    0E0
    321
    EEE
    CCC
    3D0
    */

    return 0;
}

void HeapSort(Hexa_num a[], int n)
{
    Heap heap;
    InitHeap(&heap);
    // Insert all elements to the heap.
    for (int i = 0; i < n; i++)
        Insert(&heap, a[i]);

    // Remove all elements from the heap.
    for (int i = 0; i <= n - 1; i++)
        a[i] = Delete(&heap);

    for (int i = 0; i < n; i++)
        printf("%c%c%c\n", a[i].large, a[i].middle, a[i].small);
}

Hexa_num *CreateHexaNum(int n)
{
    char a[4];
    Hexa_num *res = (Hexa_num *)malloc(sizeof(Hexa_num) * (n));
    for (int i = 0; i < n; i++)
    {
        scanf("%s", a);
        res[i].large = a[0];
        res[i].middle = a[1];
        res[i].small = a[2];
    }
    return res;
}

void GetInput()
{
    int n;
    Hexa_num *data;
    scanf("%d", &n);
    data = CreateHexaNum(n);
    HeapSort(data, n);
}

/* Modify from here */

void InitHeap(Heap *pheap)
{
    pheap->num = 0;
}

bool IsEmpty(Heap *pheap)
{
    return pheap->num == 0;
}

bool IsFull(Heap *pheap)
{
    return pheap->num == MAX_HEAP;
}

void Insert(Heap *pheap, Hexa_num data)
{
    PNode newNode;
    int idx = pheap->num + 1;
    if (IsFull(pheap))
    {
        exit(1);
    }

    while (idx > 1)
    {
        int parent = GetParent(idx);
        char Ps = pheap->items[parent].data.small;
        char Pm = pheap->items[parent].data.middle;
        char Pl = pheap->items[parent].data.large;

        char Cs = data.small;
        char Cm = data.middle;
        char Cl = data.large;

        if (Cl < Pl)
        {
            pheap->items[idx] = pheap->items[parent];
            idx = parent;
        }

        else if (Cl == Pl)
        {
            if (Cm < Pm)
            {
                pheap->items[idx] = pheap->items[parent];
                idx = parent;
            }

            else if (Cm == Pm)
            {
                if (Cs < Ps)
                {
                    pheap->items[idx] = pheap->items[parent];
                    idx = parent;
                }
                else
                    break;
            }
            else
                break;
        }
        else
            break;
    }
    newNode.data = data;
    pheap->items[idx] = newNode;
    pheap->num++;
}

Hexa_num Delete(Heap *pheap)
{
    Hexa_num min = pheap->items[1].data;

    PNode last = pheap->items[pheap->num];
    int parent = 1, child;
    while (((child = GetHighPrioityChild(pheap, parent))))
    {
        //Min_Heap 이므로 작은 값이 우선순위가 높음
        //자식 노드 중 값이 작은 것이 child에 들어있음
        char Ls = last.data.small;
        char Lm = last.data.middle;
        char Ll = last.data.large;

        char Cs = pheap->items[child].data.small;
        char Cm = pheap->items[child].data.middle;
        char Cl = pheap->items[child].data.large;

        //Min_Heap이므로 child가 작으면 parent와 바꿔야함
        //parent는 계속해서 업데이트 됨
        if (Cl < Ll)
        {
            pheap->items[parent] = pheap->items[child];
            parent = child;
        }

        else if (Cl == Ll)
        {
            if (Cm < Lm)
            {
                pheap->items[parent] = pheap->items[child];
                parent = child;
            }

            else if (Cm == Lm)
            {
                if (Cs < Ls)
                {
                    pheap->items[parent] = pheap->items[child];
                    parent = child;
                }
                else
                    break;
            }
            else
                break;
        }
        else
            break;
    }

    pheap->items[parent] = last;
    pheap->num--;

    return min;
    //가장 위의 값 출력해야 하므로
}

int GetParent(int idx)
{
    return idx / 2;
}

int GetLeftChild(int idx)
{
    return idx * 2;
}

int GetRightChild(int idx)
{
    return idx * 2 + 1;
}

int GetHighPrioityChild(Heap *pheap, int idx)
{
    if (GetLeftChild(idx) > pheap->num)
    {
        return 0;
    }
    //no child nodes

    else if (GetLeftChild(idx) == pheap->num)
    {
        return GetLeftChild(idx);
    }
    //exist only leftchild

    else
    {
        int left = GetLeftChild(idx);
        int right = GetRightChild(idx);

        char Ls = pheap->items[left].data.small;
        char Lm = pheap->items[left].data.middle;
        char Ll = pheap->items[left].data.large;

        char Rs = pheap->items[right].data.small;
        char Rm = pheap->items[right].data.middle;
        char Rl = pheap->items[right].data.large;

        if (Ll < Rl)
        {
            return left;
        }
        else if (Ll == Rl)
        {
            if (Lm < Rm)
            {
                return left;
            }
            else if (Lm == Rm)
            {
                if (Ls <= Rs)
                {
                    return left;
                }
                else
                {
                    return right;
                }
            }
            else
            {
                return right;
            }
        }
        else
        {
            return right;
        }
    }
}

/* Modify to here */
