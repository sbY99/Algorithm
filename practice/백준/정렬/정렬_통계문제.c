#include <stdio.h>
#include <stdlib.h>

//백준 2108번
typedef struct _heap
{
    int num;
    int arr[500001];
} Heap;

void Init(Heap *heap, int n);
void Create(Heap *heap, int item);
int Remove(Heap *heap);
int GetParent(int n);
int GetChild(Heap *heap, int n);
void HeapSort(Heap *heap, int arr[], int n);

int mean(int *arr, int n);
int median(int *arr, int n);
int mode(int *arr, int n);
int range(int *arr, int n);

int main()
{
    int n;
    scanf("%d", &n);
    Heap heap;
    int array[500001];
    for (int i = 0; i < n; i++)
    {
        int item;
        scanf("%d", &item);
        Create(&heap, item);
    }
    HeapSort(&heap, array, n);
    printf("%d\n", mean(array, n));
    printf("%d\n", median(array, n));
    printf("%d\n", mode(array, n));
    printf("%d", range(array, n));

    return 0;
}

int mean(int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }
    if (sum > 0)
    {
        if (sum % n < (n + 1) / 2)
        {
            return sum / n;
        }
        else
        {
            return (sum / n) + 1;
        }
    }
    else if (sum < 0)
    {
        int k = (sum % n) * -1;
        if (k > (n + 1) / 2)
        {
            return (sum / n) - 1;
        }
        else
        {
            return sum / n;
        }
    }
    else
    {
        return 0;
    }
}

int median(int *arr, int n)
{
    return arr[n / 2];
}

int mode(int *arr, int n)
{
    //음수 및 0 포함하여 8001개의 숫자 (-4000~4000)가 가능함
    int temp[8001] = {
        0,
    };
    for (int i = 0; i < n; i++)
    {
        int k = arr[i];
        temp[k + 4000]++;
    }
    int max = 0;
    for (int i = 0; i < 8001; i++)
    {
        if (max < temp[i])
        {
            max = temp[i];
        }
    }
    int where, count = 0;
    for (int i = 0; i < 8001; i++)
    {
        if (max == temp[i])
        {
            where = i - 4000;
            if (count == 1)
            {
                return where;
            }
            count++;
        }
    }
    return where;
}

int range(int *arr, int n)
{
    return arr[n - 1] - arr[0];
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