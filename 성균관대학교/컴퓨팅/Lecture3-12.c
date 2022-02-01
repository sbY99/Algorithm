//
//  Lecture3-1.c
//  3학년 1학기
//
//  Created by SB on 2021/10/02.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define Swap(x,y) do{int t=x; x=y; y=t;}while(0)

int arr[MAX_SIZE];
int n=0; // 0인덱스는 비워놓음



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

void buildHeap(void){
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
    }
    for(int i=n/2;i>=1;i--){
        downHeap(i);
    }
    
}

void printHeap(void){
    for(int j=1;j<=n;j++){
        printf(" %d",arr[j]);
    }
}

int main(){
    scanf("%d",&n);
    buildHeap();
    printHeap();
    return 0;
}
