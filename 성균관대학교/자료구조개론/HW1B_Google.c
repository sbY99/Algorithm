//
//  2018313555_HW1B.c
//  3학년 1학기
//
//  Created by SB on 2021/09/22.
//

#include <stdio.h>
#include <stdlib.h>


int a = 0;

void recursion(int *ary, int n, int x)
{
    for (int i = 0; i <= 3; i++)
    {
       ary[a] = i;
       if (a == n - 1)
        {
            int total = 0;
            for (int j = 0; j < n; j++){
                total += ary[j];
            }
 
            if (total == x)
            {
                for (int k = 0; k < n; k++)
                    printf("%d", ary[k]);
                printf("\n");
                return;
            }
        }
        else
        {
            a++;
            recursion(ary, n, x);
            a--;
        }
    }
}
 
int main()
{
    int n, x;
    scanf("%d",&n);
    scanf("%d",&x);
    int *ary=malloc(sizeof(int)*n);
    recursion(ary, n, x);
 
    return 0;
}
