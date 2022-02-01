//
//  Lecture2-2.c
//  3학년 1학기
//
//  Created by SB on 2021/09/10.
//

#include <stdio.h>
#include <stdlib.h>

void insertion(int arr[], int n){
    for(int i=1;i<n;i++){
        int temp=arr[i];
        for(int j=0;j<i;j++){
            if(arr[j]>temp){
                int t=arr[j];
                arr[j]=temp;
                temp=t;
            }
        }
        arr[i]=temp;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    
    int *arr=malloc(sizeof(int)*n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    
    insertion(arr,n);
    
    for(int i=0;i<n;i++){
        printf(" %d",arr[i]);
    }
    
    return 0;
}
