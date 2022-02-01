//
//  practice2.c
//  3학년 1학기
//
//  Created by SB on 2021/09/07.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node{
    int data;
    struct node * left;
    struct node * right;
}Node;


void add(Node *p){
    int mid,left,right;
    scanf("%d %d %d",&mid,&left,&right);
    getchar();
    
    Node *lt=malloc(sizeof(Node));
    Node *rt=malloc(sizeof(Node));
    
    p->left=lt;
    p->right=rt;
    
    p->data=mid;
    lt->data=left;
    rt->data=right;
    
    if(left!=0){
        add(p->left);
    }
    if(right!=0){
        add(p->right);
    }
    return;
}


void search(Node *p){
    char arr[100];
    scanf("%s",arr);
    getchar();
    int n=strlen(arr);
    printf(" %d",p->data);
    for(int i=0;i<n;i++){
        if(arr[i]=='L'){
            p=p->left;
            printf(" %d",p->data);
        }
        if(arr[i]=='R'){
            p=p->right;
            printf(" %d",p->data);
        }
    }
    printf("\n");
    return;
}

int main(){
    int n,m;
    Node tree;
    scanf("%d",&n);
    getchar();
    add(&tree);

    scanf("%d",&m);
    getchar();
    for(int i=0;i<m;i++){
        search(&tree);
    }
    
    return 0;
}
