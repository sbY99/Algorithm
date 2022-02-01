//
//  Lecture2-1.c
//  3학년 1학기
//
//  Created by SB on 2021/09/10.
//

#include <stdio.h>
#include <stdlib.h>
#define swap(type,x,y) do{type t=x; x=y; y=t;}while(0)

void selection(int arr[], int n){
    for(int i=n-1;i>0;i--){
        int max=i;
        for(int j=i-1;j>=0;j--){
            if(arr[j]>arr[max]){
                max=j;
            }
        }
        swap(int,arr[i],arr[max]);
    }
    
}


int main(){
    int n;
    scanf("%d",&n);
    
    int *arr=malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    selection(arr,n);
    for(int i=0;i<n;i++){
        printf(" %d",arr[i]);
    }
    return 0;
}
