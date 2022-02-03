#include <stdio.h>
#include <stdlib.h>

//힙 인덱스 1부터 구현
//자식/2 = 부모, 부모 왼쪽 = 부모/2, 부모 오른쪽 = 부모/2 +1
#define MAX_SIZE 100

int heap[MAX_SIZE];
int heapSize = 0;

void Init()
{
    heapSize = 0;
}

void heapPush(int value)
{
    if (heapSize >= MAX_SIZE)
    {
        printf("queue is full");
        return;
    }

    heap[++heapSize] = value; //마지막 노드에 값 추가(인덱스 1부터)

    int current = heapSize;
    //부모와 자식 노드 비교
    while (current / 2 >= 1 && heap[current] < heap[(current) / 2])
    {
        //자식의 우선순위가 더 높으면 (값이 작으면: 오름 차순 정렬)
        int temp = heap[current / 2];
        heap[current / 2] = heap[current];
        heap[current] = temp;
        current = current / 2;
    }
}

int heapPop()
{
    if (heapSize <= 0)
    {
        printf("queue is empty");
        return -1;
    }

    int value = heap[1];
    heap[1] = heap[heapSize--]; //마지막 값을 루트로 올림(인덱스 1부터이므로)

    int current = 1;

    //자식이 있으면 반복문 실행
    while (current * 2 <= heapSize)
    {
        int childIdx;

        //자식노드가 하나밖에 없음
        if (current * 2 == heapSize)
        {
            childIdx = current * 2;
        }
        else
        {
            //자식 노드 중 작은 값을 (우선순위가 높은 값을) 자식 인덱스에 넣음
            childIdx = heap[current * 2] < heap[current * 2 + 1] ? current * 2 : current * 2 + 1;
        }

        //만약 현재 값이 자식보다 작다면 우선순위가 알맞은 것이므로
        //바꿀 필요 없음 -> 반복문 탈출
        if (heap[current] < heap[childIdx])
        {
            break;
        }

        //우선순위에 따라 값 교체
        int temp = heap[current];
        heap[current] = heap[childIdx];
        heap[childIdx] = temp;

        //current 갱신
        current = childIdx;
    }

    return value;
}