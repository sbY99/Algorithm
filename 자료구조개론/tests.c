//
//  tests.c
//  3학년 1학기
//
//  Created by SB on 2021/10/03.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Swap(x,y) do{char t=x; x=y; y=t;}while(0)
int alphabet[26]={0,};

typedef enum {false, true} bool;

bool IsPalindrome(int n){
    int odd=0;
    for(int i=0;i<26;i++){
        if(alphabet[i]%2!=0)
            odd++; //알파벳 개수가 홀수인 경우 확인
    }
    if(n%2==0){
        if(odd>0)
            return false;
    }//문장 길이가 짝수면 알파벳 개수가 홀수인 경우가 존재하면 불가능
    if(n%2!=0){
        if(odd>1)
            return false;
    }//문장 길이가 홀수면 알파벳 개수가 홀수인 경우가 2개 이상 존재하면 불가능
    return true;
}

char OddIs(int alphabet[]){
    char Odd=0;
    for(int i=0;i<26;i++){
        if(alphabet[i]%2!=0){
            Odd='A'+i;
            break;
        }
    }
    return Odd;
}

void Make_Even_Palindrome(char in[],int n){
    int check=0;
    //한 번의 스왑으로 두 개의 문자가 매칭되는 경우
    for(int i=0;i<n;i++){
        if(in[i]!=in[n-i-1]){
        //바꾸지 않은 맨처음과 맨끝이 다르면
            for(int j=i+1;j<n;j++){
                if(in[j]==in[i]){
                    if(in[n-i-1]==in[n-j-1]){
                        Swap(in[j],in[n-i-1]);
                        printf("%s\n",in);
                        check++;
                        break;
                    }
                }
            }
        }
    }
    //위의 경우에 만족하지 않는 경우에 대해 스왑 실행
    for(int i=0;i<n;i++){
        if(in[i]!=in[n-i-1]){
            int idx=i+1;
            while(in[i]!=in[idx]){
                idx++;
            }
            Swap(in[idx],in[n-i-1]);
            //찾은경우 바꾸지 않은 마지막 인덱스와 바꿈
            printf("%s\n",in);
            check++;
            
            // 위의 스왑으로 인해 한번의 스왑으로 두 개의 알파벳이 매칭되는 경우 발생 가능
            // 따라서 위의 스왑이 발생했을 때만 실행
            for(int j=0;j<n;j++){
                if(in[idx]==in[j]){
                    if(j==idx)
                        continue;
                    if(in[n-idx-1]==in[n-j-1]){
                        Swap(in[j],in[n-idx-1]);
                        printf("%s\n",in);
                        check++;
                        break;
                    }
                }
            }
        }
    }
    printf("%d",check);
}

void Make_Odd_Palindrome(char in[],int n){
    int check=0;
    //개수가 홀수개인 알파벳
    char Odd=OddIs(alphabet);
    for(int i=0;i<n;i++){
        if(in[i]==Odd)
            continue;
        if(in[i]!=in[n-i-1]){
            for(int j=i+1;j<n;j++){
                if(in[j]==in[i]){
                    if(in[n-i-1]==in[n-j-1]){
                        Swap(in[j],in[n-i-1]);
                        printf("%s\n",in);
                        check++;
                        break;
                    }
                }
            }
        }
    }
    //가운데가 짝수개인 알파벳이면 홀수개인 알파벳이 올때 까지 먼저 스왑해줌
    for(int i=0;i<n;i++){
        if(in[n/2]==Odd)
            break;
        //홀수 알파벳의 반대편이 가운데 값과 같으면, 한 번의 스왑으로 두 개의 조건 충족 가능
        for(int j=0;j<n;j++){
            if(in[j]==Odd){
                if(in[n-j-1]==in[n/2]){
                    Swap(in[j],in[n/2]);
                    printf("%s\n",in);
                    check++;
                    break;
                }
            }
        }
        //위의 경우에 충족하지 않으면 임의로 가운데 값을 스왑해줌
        if(in[i]==in[n/2]){
            if(i!=n/2&&in[i]!=in[n-i-1]){
                //in[i]와 in[n-i-1]이 같으면 무한 반복 되므로
                Swap(in[n/2],in[n-i-1]);
                printf("%s\n",in);
                check++;
                i=-1;
            }
        }
    }
    
    //개수가 홀수개인 알파벳의 경우 검사하지 않고 넘김
    //이외의 경우 Even 경우와 동일하게 진행
    //한 번의 스왑으로 두 개의 문자가 매칭되는 경우
    for(int i=0;i<n;i++){
        if(in[i]==Odd)
            continue;
        if(in[i]!=in[n-i-1]){
            for(int j=i+1;j<n;j++){
                if(in[j]==in[i]){
                    if(in[n-i-1]==in[n-j-1]){
                        Swap(in[j],in[n-i-1]);
                        printf("%s\n",in);
                        check++;
                        break;
                    }
                }
            }
        }
    }
    //위의 경우에 만족하지 않는 경우에 대해 스왑 실행
    for(int i=0;i<n;i++){
        if(in[i]==Odd)
            continue;
        
        if(in[i]!=in[n-i-1]){
            int idx=i+1;
            while(in[i]!=in[idx]){
                idx++;
            }
            Swap(in[idx],in[n-i-1]);
            printf("%s\n",in);
            check++;
            
            // 위의 스왑으로 인해 한번의 스왑으로 두 개의 알파벳이 매칭되는 경우 발생 가능
            // 따라서 위의 스왑이 발생했을 때만 실행
            for(int j=0;j<n;j++){
                if(in[idx]==in[j]){
                    if(idx==j)
                        continue;
                    if(in[n-idx-1]==in[n-j-1]){
                        Swap(in[j],in[n-idx-1]);
                        printf("%s\n",in);
                        check++;
                        break;
                    }
                }
            }
        }
    }
    printf("%d",check);
}

int main(){
    char in[100];
    scanf("%s",in);
    int n=strlen(in);
    for(int i=0;i<n;i++){
        alphabet[in[i]-'A']++; //각각의 인덱스에 알파벳 개수 저장
    }
    if(IsPalindrome(n)==0){
        printf("Impossible");
    }
    else{
        if(n%2==0)
            Make_Even_Palindrome(in,n);
        else
            Make_Odd_Palindrome(in,n);
    }
    return 0;
}
