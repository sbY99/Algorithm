#include <stdio.h>
#include <stdlib.h>

//백준 11650번

typedef struct _location
{
    int x;
    int y;
} Loc;

typedef struct _heap
{
    int num;
    Loc loc[100001];
} Heap;

void Init(Heap *heap);
void Create(Heap *heap, Loc item);
Loc Remove(Heap *heap);
int GetParent(int n);
int GetChild(Heap *heap, int n);
void HeapSort(Heap *heap, Loc arr[], int n);

//백준 11650번
int main()
{
    int n;
    Heap heap;
    Loc temp;
    Init(&heap);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &temp.x);
        scanf("%d", &temp.y);
        Create(&heap, temp);
    }
    Loc *output = malloc(sizeof(Loc) * n);
    HeapSort(&heap, output, n);
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", output[i].x, output[i].y);
    }
    return 0;
}

void Init(Heap *heap)
{
    heap->num = 0;
}

void Create(Heap *heap, Loc item)
{
    //힙의 인덱스는 1부터 시작함
    int idx = heap->num + 1;
    int parent = GetParent(idx);
    while (parent >= 1)
    {
        int x = heap->loc[parent].x;
        int y = heap->loc[parent].y;
        if (x < item.x)
        {
            break;
        }
        if (x == item.x)
        {
            if (y < item.y)
            {
                break;
            }
        }
        heap->loc[idx] = heap->loc[parent];
        idx = parent;
        parent = GetParent(idx);
    }
    heap->loc[idx] = item;
    heap->num++;
}

Loc Remove(Heap *heap)
{
    Loc min;
    min.x = heap->loc[1].x;
    min.y = heap->loc[1].y;
    int parent = 1;
    int last = heap->num;
    int child = GetChild(heap, 1);

    int last_x = heap->loc[last].x;
    int last_y = heap->loc[last].y;
    while (child != 0)
    {
        int child_x = heap->loc[child].x;
        int child_y = heap->loc[child].y;
        if (child_x < last_x)
        {
            heap->loc[parent] = heap->loc[child];
            parent = child;
        }
        if (child_x == last_x && child_y < last_y)
        {
            heap->loc[parent] = heap->loc[child];
            parent = child;
        }
        else
        {
            break;
        }
        child = GetChild(heap, parent);
    }
    heap->loc[parent] = heap->loc[last];
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
        int left_x = heap->loc[left].x;
        int left_y = heap->loc[left].y;
        int right_x = heap->loc[right].x;
        int right_y = heap->loc[right].y;
        if (left_x < right_x)
        {
            return left;
        }
        if (left_x == right_x && left_y < right_y)
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}

void HeapSort(Heap *heap, Loc arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = Remove(heap);
    }
}