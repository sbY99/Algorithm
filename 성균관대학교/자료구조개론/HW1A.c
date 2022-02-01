//
//  HW1A.c
//  3학년 1학기
//
//  Created by SB on 2021/09/10.
//

#include <stdio.h>

int main(){
    int arr[5]={1,2,3,4,5};
    int *ptr1=&arr[1];
    printf("%d",*(ptr1+1));
    return 0;
}
