//
//  Lecture4-1.c
//  3학년 1학기
//
//  Created by SB on 2021/10/06.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define Swap(x,y) do{int t=x; x=y; y=t;}while(0)

int arr[MAX_SIZE];
int n=0; // 0인덱스는 비워놓음
int m=0; //print를 위함


void downHeap(int i){
    for(int j=i;j<=n/2;j++){
        int left=arr[j*2];
        int right=arr[j*2+1];
        int child=left;
        int index=j*2;
        if(j*2+1<=n&&left<=right){
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

void inPlaceHeapSort(void){
    buildHeap();
    for(int i=n;i>0;i--){
        Swap(arr[1],arr[i]);
        n--;
        downHeap(1);
    }
}

void printArray(void){
    for(int j=1;j<=m;j++){
        printf(" %d",arr[j]);
    }
}

int main(){
    scanf("%d",&n);
    m=n;
    inPlaceHeapSort();
    printArray();
    return 0;
}
