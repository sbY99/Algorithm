//
//  2018313555_HW1A.c
//  3학년 1학기
//
//  Created by SB on 2021/09/21.
//

#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, x;
    fscanf(stdin,"%d",&n);
    fscanf(stdin,"%d",&x);
    int *ary=malloc(sizeof(int)*n);
    int num=0, check=1;
    for(int i=0;i<n;i++){
        check*=4;
    }
    while(num!=check){
        int temp=num;
        int sum=0;
        for(int i=n-1;i>=0;i--){
            ary[i]=temp%4;
            temp/=4;
        }
        for(int i=0;i<n;i++){
            sum+=ary[i];
        }
        if(sum==x){
            for(int i=0;i<n;i++){
                fprintf(stdout,"%d",ary[i]);
            }
            fprintf(stdout,"\n");
        }
        num++;
    }
    free(ary);
    return 0;
}
