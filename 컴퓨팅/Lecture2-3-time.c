//
//  Lecture2-3-time.c
//  3학년 1학기
//
//  Created by SB on 2021/09/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
double start1, end1, start2, end2;

void reverse(int arr[], int n){
    int temp;
    for(int i=0;i<n;i++){
        for(int j=0;j<n-1;j++){
            if(arr[j]<arr[j+1]){
                temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}


void selection(int arr[], int n){
    int temp;
    for(int i=n-1;i>0;i--){
        int max=i;
        for(int j=i-1;j>=0;j--){
            if(arr[j]>arr[max]){
                max=j;
            }
        }
        temp=arr[i];
        arr[i]=arr[max];
        arr[max]=temp;
    }
    
}

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
    int n;
    scanf("%d",&n);
    int *arr1=malloc(sizeof(int)*n);
    int *arr2=malloc(sizeof(int)*n);
    
    srand(time(NULL));
    for(int i=0;i<n;i++){
        arr1[i]=rand()%100;
        arr2[i]=rand()%100;
    }
    reverse(arr1,n);
    reverse(arr2,n);
    
    
    start1=(double)clock()/CLOCKS_PER_SEC;
    selection(arr1,n);
    end1=(((double)clock())/CLOCKS_PER_SEC);
    
    
    start2=(double)clock()/CLOCKS_PER_SEC;
    insertion(arr2,n);
    end2=(((double)clock())/CLOCKS_PER_SEC);

    
    
    printf("%lf %lf\n",(end1-start1),(end2-start2));
    return 0;
}
