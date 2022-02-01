//
//  practice.c
//  practice
//
//  Created by SB on 2021/07/24.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct library{
    char writer[10];
    char title[20];
    int page;
    
}lib;

int main(){
    lib *arr[3];
    
    for(int i=0; i<sizeof(arr)/sizeof(lib *);i++){
        arr[i]=malloc(sizeof(struct library));
        ///구조체 포인터는 malloc을 통해 메모리를 할당해줘야함.
        scanf("%s",arr[i]->writer);
        scanf("%s",arr[i]->title);
        scanf("%d",&arr[i]->page);
        printf("%s %s %d\n",arr[i]->writer,arr[i]->title,arr[i]->page);
        free(arr[i]);
    }
    
    return 0;
}

