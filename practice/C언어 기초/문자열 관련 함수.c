//
//  practice.c
//  practice
//
//  Created by SB on 2021/08/13.
//

#include <stdio.h>
#include <string.h>

typedef struct Database{
    char name[10];
    char number[10];
    
}db;

int main(){
    db arr[5];
    int i=0;
    char check[10];
    while(1){
        int a;
        printf("****MENU****\n");
        printf("1. INSERT\n");
        printf("2. Delete\n");
        printf("3. Search\n");
        printf("4. Print All\n");
        printf("5. Exit\n");
        scanf("%d",&a);
        if(a==1){
            printf("[INSERT]");
            printf("Input Name:");
            scanf("%s",arr[i].name);
            printf("Input Tel Number:");
            scanf("%s",arr[i].number);
            printf("Data Inserted\n");
            i++;
        }
        if(a==2){
            printf("[DELETE]");
            printf("Input Name:");
            scanf("%s",check);
            for(int j=0;j<i;j++){
                if(strcmp(arr[j].name,check)==0){
                    ///문자열간의 비교는 strcmp 사용
                    for(int k=j;k<i-1;k++){
                        strcpy(arr[k].name,arr[k+1].name);
                        strcpy(arr[k].number,arr[k+1].number);
                        ///문자열 대입은 strcpy 사용
                        ///인덱스 j에 해당하는 문자열을 삭제하는 반복문임.
                    }
                }
            }
            i--;
        }
        if(a==3){
            printf("[SEARCH]");
            printf("Input Name:");
            scanf("%s",check);
            for(int j=0;j<i;j++){
                if(strcmp(arr[j].name,check)==0){
                    printf("%s\n",arr[j].name);
                    printf("%s\n",arr[j].number);
                }
            }
        }
        if(a==4){
            printf("[PRINT ALL]");
            for(int j=0;j<i;j++){
                printf("%s\n",arr[j].name);
                printf("%s\n",arr[j].number);
            }
        }
        if(a==5) break;
    }
    
    return 0;
}
