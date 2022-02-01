//
//  practice.c
//  practice
//
//  Created by SB on 2021/08/29.
//

#include <stdio.h>
#include <stdlib.h>

//백준 2751

typedef struct _heap
{
    int num;
    int arr[1000001];
} Heap;

void Init(Heap *heap, int n);
void Create(Heap *heap, int item);
int Remove(Heap *heap);
int GetParent(int n);
int GetChild(Heap *heap, int n);
void HeapSort(Heap *heap, int arr[], int n);

int main()
{
    int n;
    scanf("%d", &n);
    Heap heap;
    Init(&heap, n);
    for (int i = 0; i < n; i++)
    {
        int item;
        scanf("%d", &item);
        Create(&heap, item);
    }
    int *output = malloc(sizeof(int) * n);
    HeapSort(&heap, output, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", output[i]);
    }
    return 0;
}

void Init(Heap *heap, int n)
{
    heap->num = 0;
}

void Create(Heap *heap, int item)
{
    //힙의 인덱스는 1부터 시작함
    int idx = heap->num + 1;
    int parent = GetParent(idx);
    while (parent >= 1)
    {

        if (heap->arr[parent] < item)
        {
            break;
        }
        heap->arr[idx] = heap->arr[parent];
        idx = parent;
        parent = GetParent(idx);
    }
    heap->arr[idx] = item;
    heap->num++;
}

int Remove(Heap *heap)
{
    int min = heap->arr[1];

    int parent = 1;
    int last = heap->num;
    int child = GetChild(heap, 1);
    while (child != 0)
    {
        if (heap->arr[child] < heap->arr[last])
        {
            heap->arr[parent] = heap->arr[child];
            parent = child;
        }
        else
        {
            break;
        }
        child = GetChild(heap, parent);
    }
    heap->arr[parent] = heap->arr[last];
    heap->num--;
    return min;
}

int GetParent(int n)
{
    return n / 2;
}

int GetChild(Heap *heap, int n)
{
    int left = n * 2;
    int right = n * 2 + 1;
    //자식 없음
    if (heap->num < left)
    {
        return 0;
    }
    //왼쪽 자식만 있음
    else if (heap->num == left)
    {
        return left;
    }
    else
    {
        if (heap->arr[left] > heap->arr[right])
        {
            return right;
        }
        else
        {
            return left;
        }
    }
}

void HeapSort(Heap *heap, int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = Remove(heap);
    }
}