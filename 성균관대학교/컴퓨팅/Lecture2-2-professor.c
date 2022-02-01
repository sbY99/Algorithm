//
//  Lecture2-2-professor.c
//  3학년 1학기
//
//  Created by SB on 2021/09/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double start, end;


void insertion(int arr[], int n){
    int save, j;
    
    
    for(int pass=1; pass<n; pass++){ ///2번째 부터 마지막 까지
        save=arr[pass]; /// 현재 값 임시 변수에 저장
        j=pass-1; /// j는 현재 위치 pass에서 아래로 순회
        while((j>=0)&&(arr[j]>save)){ ///j가 0보타 크면서 현재값보다 크면
            arr[j+1]=arr[j];
            j--;
        }
        arr[j+1]=save; ///임시 저장한 변수를 당겨진 위치로 이동
    }
    
}

int main(){
    start=(double)clock()/CLOCKS_PER_SEC;
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
    printf("\n");
    
    end=(((double)clock())/CLOCKS_PER_SEC);
    printf("%lf\n",(end-start));
    return 0;
}
