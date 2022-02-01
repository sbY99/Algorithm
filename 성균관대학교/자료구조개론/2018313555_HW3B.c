//
//  2018313555_HW3B.c
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
void preorder(QuadTreeNode *root);
void inorder(QuadTreeNode *root);
void postorder(QuadTreeNode *root);
int countNodes(QuadTreeNode *root);
QuadTreeNode *leftMost(QuadTreeNode *node);
/* Modify from here */

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

  preorder(node1);
  printf("\n");
  inorder(node1);
  printf("\n");
  postorder(node1);
  printf("\n");
  printf("%d\n", countNodes(node1));

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

void preorder(QuadTreeNode *root)
{
  printf("%d ", root->item);
  if (root->left_child != NULL)
  {
    preorder(root->left_child);
  }
  if (root->middle1_child != NULL)
  {
    preorder(root->middle1_child);
  }
  if (root->middle2_child != NULL)
  {
    preorder(root->middle2_child);
  }
  if (root->right_child != NULL)
  {
    preorder(root->right_child);
  }
}

void postorder(QuadTreeNode *root)
{
  if (root->left_child != NULL)
  {
    postorder(root->left_child);
  }

  if (root->middle1_child != NULL)
  {
    postorder(root->middle1_child);
  }
  if (root->middle2_child != NULL)
  {
    postorder(root->middle2_child);
  }
  if (root->right_child != NULL)
  {
    postorder(root->right_child);
  }

  printf("%d ", root->item);
}

void inorder(QuadTreeNode *root)
{
  if (root->left_child != NULL)
  {
    inorder(root->left_child);
  }
  if (root->middle1_child != NULL)
  {
    inorder(root->middle1_child);
  }
  printf("%d ", root->item);
  if (root->middle2_child != NULL)
  {
    inorder(root->middle2_child);
  }
  if (root->right_child != NULL)
  {
    inorder(root->right_child);
  }
}

int countNodes(QuadTreeNode *root)
{
  int l = 0, m1 = 0, m2 = 0, r = 0;
  if (root->left_child != NULL)
  {
    l = countNodes(root->left_child);
  }
  if (root->middle1_child != NULL)
  {
    m1 = countNodes(root->middle1_child);
  }
  if (root->middle2_child != NULL)
  {
    m2 = countNodes(root->middle2_child);
  }
  if (root->right_child != NULL)
  {
    r = countNodes(root->right_child);
  }
  return 1 + l + m1 + m2 + r;
}

/* Modify to here */
