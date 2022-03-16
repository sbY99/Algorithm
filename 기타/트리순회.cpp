#include <iostream>
#include <vector>
using namespace std;

int N;
char Tree[27][3];

void preorder(char curr)
{
    printf("%c", curr);
    for (int i = 0; i < N; i++)
    {
        if (Tree[i][0] == curr)
        {
            if (Tree[i][1] != '.')
            {
                preorder(Tree[i][1]);
            }
            if (Tree[i][2] != '.')
            {
                preorder(Tree[i][2]);
            }
            break;
        }
    }
}

void inorder(char curr)
{
    for (int i = 0; i < N; i++)
    {
        if (Tree[i][0] == curr)
        {
            if (Tree[i][1] != '.')
            {
                inorder(Tree[i][1]);
            }
            printf("%c", curr);
            if (Tree[i][2] != '.')
            {
                inorder(Tree[i][2]);
            }
            break;
        }
    }
}

void postorder(char curr)
{
    for (int i = 0; i < N; i++)
    {
        if (Tree[i][0] == curr)
        {
            if (Tree[i][1] != '.')
            {
                postorder(Tree[i][1]);
            }
            if (Tree[i][2] != '.')
            {
                postorder(Tree[i][2]);
            }
            printf("%c", curr);
            break;
        }
    }
}
int main()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        char p1, c1, c2;
        cin >> p1 >> c1 >> c2;

        Tree[i][0] = p1;
        Tree[i][1] = c1;
        Tree[i][2] = c2;
    }
    preorder('A');
    printf("\n");
    inorder('A');
    printf("\n");
    postorder('A');
}