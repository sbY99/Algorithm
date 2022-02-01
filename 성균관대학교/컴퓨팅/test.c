

#include <stdio.h>
int main(void)
{
    printf("한글5개 입력: %d\n", sizeof("안녕하ㅅㅇ"));
    printf("한글1개 입력: %d\n", sizeof("닭"));
    printf("한글1개 영어1개 입력: %d\n", sizeof("d홍"));
}