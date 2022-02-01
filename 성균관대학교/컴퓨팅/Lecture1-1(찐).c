#include <stdio.h>
#include <stdlib.h>

typedef struct dnode{
    char data;
    struct dnode *prev;
    struct dnode *next;
}Dnode;

typedef struct dlist{
    Dnode *head;
    Dnode *tail;
    int count;
}Dlist;


void add(Dlist *list){
    int position;
    char item;
    scanf("%d %c",&position, &item);
    getchar();
    if((list->count)+1<position){
        printf("invalid position\n");
        return;
    }
    Dnode *p=malloc(sizeof(Dnode));
    (list->count)++;
    p->data=item;
    Dnode *ptr=list->head;
    for(int i=1;i<position;i++){
        ptr=ptr->next;
    }
    p->prev=ptr;
    p->next=ptr->next;
    ptr->next=ptr->next->prev=p;
}

void delete(Dlist *list){
    int position;
    scanf("%d",&position);
    getchar();
    if(list->count<position){
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
    
    (list->count)--;
}

void get_entry(Dlist *list){
    int position;
    scanf("%d",&position);
    getchar();
    if(list->count<position){
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
    Dnode *ptr=list->head;
    for(int i=0;i<list->count;i++){
        ptr=ptr->next;
        printf("%c",ptr->data);
    }
    printf("\n");
}

void Initialize(Dlist *list){
    Dnode *dhead=malloc(sizeof(Dnode));
    Dnode *dtail=malloc(sizeof(Dnode));
    list->head=dtail->prev=dhead;
    list->tail=dhead->next=dtail;
    dhead->prev=dtail->next=NULL;
    
    list->count=0;
}


int main(void)
{
    int num;
    char check;
    Dlist list;
    Initialize(&list);
 
    scanf("%d", &num);
    getchar();
    for (int i = 0; i < num; i++) {
        scanf("%c", &check);
        getchar();
         
        if (check == 'A') {
            add(&list);
            continue;
        }
        else if (check == 'D') {
            delete(&list);
            continue;
        }
        else if (check == 'G') {
            get_entry(&list);
            continue;
        }
        else if (check == 'P') {
            print(&list);
            continue;
        }
    }
 
    return 0;
}
