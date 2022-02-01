//
//  2018313555_HW3C.c
//  3학년 1학기
//
//  Created by SB on 2021/11/01.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* Modify from here */

/* Modify to here */

typedef int QuadData;

typedef struct _QuadTreeNode
{
  QuadData item;
  struct _QuadTreeNode *left_child;
  struct _QuadTreeNode *middle1_child;
  struct _QuadTreeNode *middle2_child;
  struct _QuadTreeNode *right_child;
} QuadTreeNode;

void PrintTreeNode(QuadTreeNode *node);

QuadTreeNode *CreateNode(QuadData item);
void DestroyNode(QuadTreeNode *node);
void CreateLeftSubtree(QuadTreeNode *root, QuadTreeNode *left);
void CreateMiddle1Subtree(QuadTreeNode *root, QuadTreeNode *middle1);
void CreateMiddle2Subtree(QuadTreeNode *root, QuadTreeNode *middle2);
void CreateRightSubtree(QuadTreeNode *root, QuadTreeNode *right);
void levelorder(QuadTreeNode *root);
QuadTreeNode *leftMost(QuadTreeNode *node);
/* Modify from here */

typedef enum
{
  false,
  true
} bool;

typedef struct _Qnode
{
  QuadTreeNode *data;  //노드의 주소값을 의미, 큐에 들어가는 값이라고 생각하면 됨(int n과 같이)
  struct _Qnode *next; //노드를 가리키는 포인터로서 큐의 다음 노드를 가리킴
} QNode;

typedef struct
{
  QNode *front; //큐의 맨앞을 가리킴,
  QNode *rear;  //큐의 맨뒤를 가리킴
} DQueue;

void InitQueue(DQueue *pqueue);
bool IsEmpty(DQueue *pqueue);
void EnQueue(DQueue *pqueue, QuadTreeNode *data); //트리 노드를 삽입
QuadTreeNode *Dequeue(DQueue *pqueue);            //트리 노드를 반환

/* Modify to here */

int main()
{
  QuadTreeNode *node1 = CreateNode(1);
  QuadTreeNode *node2 = CreateNode(2);
  QuadTreeNode *node3 = CreateNode(3);
  QuadTreeNode *node4 = CreateNode(4);
  QuadTreeNode *node5 = CreateNode(5);
  QuadTreeNode *node6 = CreateNode(6);
  QuadTreeNode *node7 = CreateNode(7);
  QuadTreeNode *node8 = CreateNode(8);
  QuadTreeNode *node9 = CreateNode(9);

  CreateLeftSubtree(node1, node2);
  CreateMiddle1Subtree(node1, node3);
  CreateMiddle2Subtree(node1, node4);
  CreateRightSubtree(node1, node5);

  CreateLeftSubtree(node2, node6);
  CreateMiddle1Subtree(node2, node7);

  CreateLeftSubtree(node3, node8);
  CreateRightSubtree(node5, node9);

  PrintTreeNode(node1);
  PrintTreeNode(node2);
  PrintTreeNode(node3);
  PrintTreeNode(node4);
  PrintTreeNode(node5);
  PrintTreeNode(node6);
  PrintTreeNode(node7);
  PrintTreeNode(node8);
  PrintTreeNode(node9);

  levelorder(node1);

  DestroyNode(node1);
  DestroyNode(node2);
  DestroyNode(node3);
  DestroyNode(node4);
  DestroyNode(node5);
  DestroyNode(node6);
  DestroyNode(node7);
  DestroyNode(node8);
  DestroyNode(node9);

  return 0;
}

void PrintTreeNode(QuadTreeNode *node)
{
  printf("%d: ", node->item);
  node->left_child == NULL ? printf("null ") : printf("%d ", node->left_child->item);
  node->middle1_child == NULL ? printf("null ") : printf("%d ", node->middle1_child->item);
  node->middle2_child == NULL ? printf("null ") : printf("%d ", node->middle2_child->item);
  node->right_child == NULL ? printf("null\n") : printf("%d\n", node->right_child->item);
}

QuadTreeNode *leftMost(QuadTreeNode *node)
{
  if (node == NULL)
    return NULL;
  while (node->left_child != NULL || node->middle1_child != NULL)
  {
    if (node->left_child != NULL)
      node = node->left_child;
    else if (node->middle1_child != NULL)
      node = node->middle1_child;
  }
  return node;
}

/* Modify from here */

QuadTreeNode *CreateNode(QuadData item)
{
  QuadTreeNode *node = (QuadTreeNode *)malloc(sizeof(QuadTreeNode));
  node->item = item;
  node->left_child = NULL;
  node->middle1_child = NULL;
  node->middle2_child = NULL;
  node->right_child = NULL;
  return node;
}

void DestroyNode(QuadTreeNode *node)
{
  free(node);
}

void CreateLeftSubtree(QuadTreeNode *root, QuadTreeNode *left)
{
  if (root->left_child != NULL)
    exit(1);

  root->left_child = left;
}
void CreateMiddle1Subtree(QuadTreeNode *root, QuadTreeNode *middle1)
{
  if (root->middle1_child != NULL)
    exit(1);

  root->middle1_child = middle1;
}
void CreateMiddle2Subtree(QuadTreeNode *root, QuadTreeNode *middle2)
{
  if (root->middle2_child != NULL)
    exit(1);

  root->middle2_child = middle2;
}
void CreateRightSubtree(QuadTreeNode *root, QuadTreeNode *right)
{
  if (root->right_child != NULL)
    exit(1);

  root->right_child = right;
}

void levelorder(QuadTreeNode *root)
{
  // DeQueue를 생성하고 루트 값을 집어넣음ㄴ
  DQueue deq;
  InitQueue(&deq);
  EnQueue(&deq, root);
  //왼쪽부터 차례로 인큐와 디큐를 실행하며 출력
  QuadTreeNode *data;
  for (data = Dequeue(&deq); data != NULL; data = Dequeue(&deq))
  {
    printf("%d ", data->item);

    if (data->left_child != NULL)
    {
      EnQueue(&deq, data->left_child);
    }
    if (data->middle1_child != NULL)
    {
      EnQueue(&deq, data->middle1_child);
    }
    if (data->middle2_child != NULL)
    {
      EnQueue(&deq, data->middle2_child);
    }
    if (data->right_child != NULL)
    {
      EnQueue(&deq, data->right_child);
    }
    }
  printf("\n");
}

void InitQueue(DQueue *pqueue)
{
  pqueue->front = pqueue->rear = NULL;
}

bool IsEmpty(DQueue *pqueue)
{
  return pqueue->front == NULL;
}

void EnQueue(DQueue *pqueue, QuadTreeNode *data)
{
  QNode *newNode = (QNode *)malloc(sizeof(QNode));
  newNode->data = data;
  newNode->next = NULL;
  //트리노드와 트리노드에 대한 포인터를 가진 노드 생성

  if (IsEmpty(pqueue))
  {
    pqueue->front = pqueue->rear = newNode;
  }
  else
  {
    pqueue->rear->next = newNode;
    //원래 맨 마지막이였던 노드의 next가 새로운 노드를 가리킴
    pqueue->rear = newNode;
    //rear이 새로운 노드를 가리킴
  }
}

QuadTreeNode *Dequeue(DQueue *pqueue)
{
  if (IsEmpty(pqueue))
  {
      return NULL;
  }
  QNode *temp = pqueue->front;    //큐의 맨 첫 번째 노드
  QuadTreeNode *del = temp->data; //큐의 맨 첫 번째 노드에 있는 트리노드의 주소값
    //QNode에는 QNode를 가리키는 Next와 데이터인 QuadTreeNode의 포인터가 있음(int a와 같은 느낌)
  if (temp->next == NULL)         //큐의 노드가 하나이면
  {
    pqueue->front = pqueue->rear = NULL;
  }
  else //큐의 노드가 두개 이상이면
  {
    pqueue->front = temp->next;
  }
  free(temp);
  return del;//실제적으로 필요한 것은 삭제되는 큐 노드안에 있는 트리 노드의 주소값
}

/* Modify to here */
