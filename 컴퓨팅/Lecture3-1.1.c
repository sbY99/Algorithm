//
//  Lecture3-1.c
//  3학년 1학기
//
//  Created by SB on 2021/09/17.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define Swap(x,y) do{int t=x; x=y; y=t;}while(0)

int arr[MAX_SIZE];
int n=0; // 0인덱스는 비워놓음

void upHeap(int i){
    for(int j=i/2;j>0;j=j/2){
        if(arr[i]>=arr[j]){
            Swap(arr[i],arr[j]);
            i/=2;
        }
        else
            break;
    }
}

void downHeap(int i){
    for(int j=i;j<=n/2;j++){
        int left=arr[j*2];
        int right=arr[j*2+1];
        int child=left;
        int index=j*2;
        if(left<=right){
            child=right;
            index=j*2+1;
        }
        if(arr[j]<=child){
            Swap(arr[j],arr[index]);
            j=index-1;
        }
        else
            break;
    }
}


void InsertItem(int key){
    arr[++n]=key;
    upHeap(n);
    printf("%d\n",0);
}

int removeMax(void){
    int root=arr[1];
    arr[1]=arr[n];
    n--;
    downHeap(1);
    return root;
}

void printHeap(void){
    for(int j=1;j<=n;j++){
        printf(" %d",arr[j]);
    }
    printf("\n");
}


int main(){
    while(1){
        char check;
        int k;
        scanf("%c",&check);
        switch(check){
            case 'i':
                scanf("%d",&k);
                InsertItem(k);
                break;
            case 'd':
                printf("%d",removeMax());
                printf("\n");
                break;
            case 'p':
                printHeap();
                break;
            case 'q':
                break;
        }
        if(check=='q')
            break;
    }

    return 0;
}
