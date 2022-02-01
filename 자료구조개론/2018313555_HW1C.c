//
//  2018313555_HW1C.c
//  3학년 1학기
//
//  Created by SB on 2021/09/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool palindrome(int arr[], int a, int b){
    if(a>=b){
        return true;
    }
    if(arr[a]!=arr[b]){
        return false;
    }
    return palindrome(arr,a+1,b-1);
}


void recursion(int arr[],int num, int n, int x){
    for(int i=0;i<4;i++){
        arr[num]=i;
        if(num==n-1){
            int sum=0;
            for(int j=0;j<n;j++){
                sum+=arr[j];
            }
            if(sum==x&&palindrome(arr,0,n-1)){
                for(int j=0;j<n;j++){
                    fprintf(stdout,"%d",arr[j]);
                }
                fprintf(stdout,"\n");
            }
        }
        else{
            recursion(arr,num+1,n,x);
        }
    }
    
}


int main(){
    int n,x;
    fscanf(stdin,"%d",&n);
    fscanf(stdin,"%d",&x);
    int *arr=malloc(sizeof(int)*n);
    recursion(arr,0,n,x);
    free(arr);
}
