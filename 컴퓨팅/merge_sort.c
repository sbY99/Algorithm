//
//  merge_sort.c
//  3학년 1학기
//
//  Created by SB on 2021/10/25.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int n;
    struct node *next;
}Node;

typedef struct{
    Node *N1;
    Node *N2;
}Temp;

Node* add(int x){
    Node *new;
    
    new=malloc(sizeof(Node));
    new->n=x;
    new->next=NULL;
    
    return new;
}

Temp partition(Node *N, int n){
    Node *p;
    Temp result;
    Node *N1, *N2;
    
    p=N;
    N1=N;
    
    for(int i=0;i<n-1;i++){
        p=p->next;
    }
    
    N2=p->next;
    
    p->next=NULL;
    
    result.N1=N1;
    result.N2=N2;
    
    return result;
}

Node *merge(Node *N1, Node *N2){
    Node *result=NULL;
    
    if(N1==NULL) return N2;
    else if (N2==NULL) return N1;
    
    if((N1->n)<(N2->n)){
        result=N1;
        result->next=merge(N1->next,N2);
    }
    //N1의 다음 원소로 넘어감
    else{
        result=N2;
        result->next=merge(N1,N2->next);
    }
    return result;
}


void mergeSort(Node **N, int n){
    Node *N1=NULL;
    Node *N2=NULL;
    Temp temp;
    
    if(n>1&& *N!=NULL){
        temp=partition(*N,n/2);
        // 반절 분할시행
        N1=temp.N1;
        N2=temp.N2;
        
        mergeSort(&N1,n/2);
        mergeSort(&N2,(int)((n/2.0)+0.5));
        //가운데 처리
        //나누어졌으면 합병 실행
        *N=merge(N1,N2);
    }
    
}

void printAll(Node *n){
    
    while(n!=NULL){
        printf(" %d",n->n);
        n=n->next;
    }
}

int main(){
    Node *head;
    int n;
    
    head=malloc(sizeof(Node));
    head->next=NULL;
    
    Node *temp;
    temp=head;
    
    scanf("%d",&n);
    
    for(int i=0;i<n;i++){
        int x;
        scanf("%d",&x);
        temp->next=add(x);
        temp=temp->next;
    }
    //temp라는 더미노드에 각 노드들을 연결함
    
    mergeSort(&head->next,n);
    printAll(head->next);
    
}
