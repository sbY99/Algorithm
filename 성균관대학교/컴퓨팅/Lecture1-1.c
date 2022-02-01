//
//  test.c
//  컴퓨팅
//
//  Created by SB on 2021/09/01.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct dnode{
    char data;
    struct dnode *prev;
    struct dnode *next;
}Dnode;

typedef struct dlist{
    Dnode *head;
    int count;
}Dlist;


void add(Dlist *list, int position, char item){
    if(position==0||(list->count)+1<position){
        printf("invalid position\n");
        return;
    }
    Dnode *p=malloc(sizeof(Dnode));
    list->count++;
    p->data=item;
    Dnode *ptr=list->head;
    for(int i=1;i<position;i++){
        ptr=ptr->next;
    }
    Dnode **dptr=&ptr;
    p->prev=ptr;
    if(position==list->count){
        p->next=NULL;
        (*dptr)->next=p;
    }
    else{
        p->next=ptr->next;
        (*dptr)->next=(*dptr)->next->prev=p;
    }
}

void delete(Dlist *list, int position){
    if(position==0||position>list->count){
        printf("invalid position\n");
        return;
    }
    
    Dnode *ptr=list->head;
    for(int i=0;i<position;i++){
        ptr=ptr->next;
    }
    ptr->prev->next=ptr->next;
    ptr->next->prev=ptr->prev;
    free(ptr);
    
    list->count--;
}

void get_entry(Dlist *list, int position){
    if(position==0||position>list->count){
        printf("invalid position\n");
        return;
    }
    Dnode *ptr=list->head;
    for(int i=0;i<position;i++){
        ptr=ptr->next;
    }
    printf("%c\n",ptr->data);
    
}

void print(Dlist *list){
    Dnode *ptr=list->head->next;
    while(ptr!=NULL){
        printf("%c",ptr->data);
        ptr=ptr->next;
    }
    printf("\n");
}

void Initialize(Dlist *list){
    Dnode *dummy=malloc(sizeof(Dnode));
    list->head=dummy;
    dummy->next=dummy->prev=NULL;
    list->count=0;
}


int main(){
    Dlist list;
    Initialize(&list);
    int n;
    scanf("%d",&n);
    getchar();
    char check[7];
    for(int i=0;i<n;i++){
        fgets(check,sizeof(check),stdin);
        switch(check[0]){
            case 'A':
                add(&list, check[2]-48, check[4]);
                break;
            case 'D':
                delete(&list,check[2]-48);
                break;
            case 'G':
                get_entry(&list,check[2]-48);
                break;
            case 'P':
                print(&list);
                break;
        }
    }
    
    return 0;
}
