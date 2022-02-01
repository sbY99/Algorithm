//
//  quick sort.c
//  3학년 1학기
//
//  Created by SB on 2021/10/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Swap(int arr[], int a, int b){
    int temp=arr[a];
    arr[a]=arr[b];
    arr[b]=temp;
}

int findPivot(int arr[],int left, int right){
    int len=right-left;
    if(len==0||len==1) return left;
    else{
        int check=0, x=-1, y=-1, z=-1, temp=0;
        int a[3];
        while(check<3){
            temp=rand()%(len+1);
            if(temp==x||temp==y)
                continue;//동일하면 다시 rand실행
            if(check==0)
                x=temp;
            if(check==1)
                y=temp;
            if(check==2)
                z=temp;
            a[check]=arr[left+temp];
            check++;
        }
        if(a[1]<=a[0]&&a[0]<=a[2]) return left+x;
        if(a[2]<=a[0]&&a[0]<=a[1]) return left+x;
        
        if(a[0]<=a[1]&&a[1]<=a[2]) return left+y;
        if(a[2]<=a[1]&&a[1]<=a[0]) return left+y;
        
        if(a[0]<=a[2]&&a[2]<=a[1]) return left+z;
        if(a[1]<=a[2]&&a[2]<=a[0]) return left+z;
        
    }
    return 0;
}


int partition(int arr[],int left,int right){
    int index=findPivot(arr,left,right);
    int pivot=arr[index];
    
    while(left<=right){
        while(left<=right&&pivot>=arr[left]){
            left++;
        }
        while(right>=left&&pivot<=arr[right]){
            right--;
        }

        if(left<=right){
            Swap(arr,left,right);
            
        }
    }
    if(index>right){
        Swap(arr,index,left);
        
        return left;
    }
        
    else if(index<right){
        Swap(arr,index,right);
        
        return right;
    }
    return index;

}


void quickSort(int arr[],int left, int right){
    if(left<right){
        int pivot=partition(arr,left,right);
        quickSort(arr,left,pivot-1);
        quickSort(arr,pivot+1,right);
        
    }
    
}


int main(){
    int n;
    scanf("%d",&n);
    int *arr=(int *)malloc(sizeof(int) * n);
    for(int i=0;i<n;i++){
        scanf("%d",&arr[i]);
    }
    quickSort(arr,0,n-1);
    
    for(int i=0;i<n;i++){
        printf(" %d",arr[i]);
    }
    return 0;
}
