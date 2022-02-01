#include <stdio.h>
#include <stdlib.h>

typedef struct NodeStruct
{
    int data;
    struct NodeStruct *leftchild;
    struct NodeStruct *rightchild;
} Node;

Node *insertItem(Node *node, int data);
Node *treeSearch(Node *node, int n);
Node *removeElement(Node *node, int n);
Node *inOrderSucc(Node *node);
void printAll(Node *node);

int c = 0;

int main()
{
    Node *root = NULL;
    char check;
    int data;
    while (1)
    {
        scanf("%c", &check);
        if (check == 'i')
        {
            scanf("%d", &data);
            root = insertItem(root, data);
            continue;
        }
        else if (check == 'd')
        {
            c = 0;
            scanf("%d", &data);
            root = removeElement(root, data);
            if (c == 0)
            {
                printf("%d\n", data);
            }
            continue;
        }
        else if (check == 's')
        {
            scanf("%d", &data);
            treeSearch(root, data);

            continue;
        }
        else if (check == 'p')
        {
            printAll(root);
            printf("\n");
            continue;
        }
        else if (check == 'q')
        {
            break;
        }
    }
    return 0;
}

Node *insertItem(Node *node, int data)
{
    if (node == NULL)
    {
        node = (Node *)malloc(sizeof(Node));
        node->data = data;
        node->leftchild = NULL;
        node->rightchild = NULL;
    }
    else if (data < node->data)
    {
        node->leftchild = insertItem((node->leftchild), data);
    }
    else
    {
        node->rightchild = insertItem((node->rightchild), data);
    }
    return node;
}

Node *treeSearch(Node *node, int n)
{
    if (node == NULL)
    {
        printf("X\n");
        return NULL;
    }
    else if (n == node->data)
    {
        printf("%d\n", n);
        return node;
    }
    else if (n < node->data)
    {
        treeSearch(node->leftchild, n);
    }
    else
    {
        treeSearch(node->rightchild, n);
    }
    return node;
}

Node *removeElement(Node *node, int n)
{
    Node *temp = NULL;
    if (node == NULL)
    {
        printf("X\n");
        c++;
        return NULL;
    }
    if (n < node->data)
    {
        node->leftchild = removeElement(node->leftchild, n);
    }
    else if (n > node->data)
    {
        node->rightchild = removeElement(node->rightchild, n);
    }
    else
    {
        if (node->rightchild != NULL && node->leftchild != NULL)
        {
            temp = inOrderSucc(node->rightchild);
            node->data = temp->data;
            node->rightchild = removeElement(node->rightchild, temp->data);
        }
        else
        {
            temp = node->leftchild == NULL ? node->rightchild : node->leftchild;
            free(node);
            return temp;
        }
        //노드의 자녀가 두개 모두 존재할 경우 오른쪽 서브트리에서 가장 작은 수 선택함
        //교체되는 노드에 이 값을 대입하고, 오른쪽 서브트리에서 이 값에 대한 삭제 진행함
    }
    return node;
}

Node *inOrderSucc(Node *node)
{
    Node *cur = node;
    while (cur && cur->leftchild != NULL)
    {
        cur = cur->leftchild;
    }
    return cur;
}

void printAll(Node *node)
{
    if (node != NULL)
    {
        printf(" %d", node->data);
        printAll(node->leftchild);
        printAll(node->rightchild);
    }
}
