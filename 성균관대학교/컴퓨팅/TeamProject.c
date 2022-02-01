//
//  TeamProject.c
//  3학년 1학기
//
//  Created by SB on 2021/11/16.
//

// 각 층에 존재하는 주차 가능 공간, 주차장 높이, 해쉬테이블의 개수
#define MAX_Palette 3
#define MAX_Height 5
#define MAX_Hash 10

//확인상 편의를 위해 실제 시간 1초 -> 1분으로 설정
//초당 금액, 최소 금액, 최대 금액
#define Parking_fee 1
#define Min_fee 3600
#define Max_fee 30000
//1시간 이후로 이용시 추가요금이 부과되는 단위(분)
//5분 단위로 추가요금 발생함
#define Plus_unit 5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

//저장되는 차량 정보들
typedef struct _palette
{
    bool Is_regular;
    char Name[20];
    char Car_type[20];
    int Car_weight;
    int Car_height;
    char Car_id[10];
    int Car_pw;
    time_t time;
    struct _palette *Next;
} Palette;

typedef struct
{
    // 해당 층에 차가 몇개 들어있는지를 의미
    int Car_num[MAX_Height];
    // 각 층에 해쉬맵 생성
    Palette *height[MAX_Height][MAX_Hash];
} Parking;

void InitParking(Parking *parking);
bool IsHeightFull(Parking *parking, int h);
bool IsHeightEmpty(Parking *parking, int h);
bool IsParkingFull(Parking *parking);
bool IsParkingEmpty(Parking *parking);
void AddData(Palette *des, Palette data);
void Clear(Parking *parking);

void CreatePalette(Parking *parking, Palette data);
void RetrievePalette(Parking *parking, Palette data);
void UpdatePalette(Parking *parking, Palette des, Palette data, int type);
void DeletePalette(Parking *parking, Palette data);

void Admin_RetrievePalette_User(Parking *parking, Palette data);
void Admin_RetrievePalette_Car(Parking *parking, Palette data);
void Admin_UpdatePalette(Parking *parking, Palette des, Palette data, int type);

void PrintAll(Parking *parking);
int Parkingfee(int diff);
bool CheckID(Parking *parking, Palette data);

int main()
{
    Parking *parking = (Parking *)malloc(sizeof(parking));
    InitParking(parking);
    int n;
    int k;
    while (1)
    {
        //입력 받는 차량 정보
        Palette data;
        printf("관리자 모드(1) 사용자 모드(2) 종료(0): ");
        scanf("%d", &k);
        //관리자 모드
        if (k == 1)
        {
            printf("관리자 모드: 검색(1) 수정(2) 종료(0): ");
            scanf("%d", &n);
            //관리자 검색 모드
            if (n == 1)
            {
                if (IsParkingEmpty(parking))
                {
                    printf("검색할 차량이 존재하지 않습니다!\n");
                    continue;
                }
                int m;
                printf("특정 차량 조회(1) 모든 차량 조회(2) 종료(0): ");
                scanf("%d", &m);
                //특정 차량 조회
                if (m == 1)
                {
                    int t;
                    printf("사용인으로 조회(1) 차량 번호로 조회(2) 종료(0): ");
                    scanf("%d", &t);
                    //사용인으로 조회
                    if (t == 1)
                    {
                        printf("사용자 이름: ");
                        scanf("%s", data.Name);
                        Admin_RetrievePalette_User(parking, data);
                    }
                    //차량 번호로 조회
                    else if (t == 2)
                    {
                        printf("차량 번호: ");
                        scanf("%s", data.Car_id);
                        Admin_RetrievePalette_Car(parking, data);
                    }
                    //종료
                    else if (t == 0)
                    {
                        break;
                    }
                    //에러
                    else
                    {
                        printf("올바르지 않은 입력입니다!\n");
                    }
                }
                //모든 차량 조회
                else if (m == 2)
                {
                    PrintAll(parking);
                }
                //종료
                else if (m == 0)
                {
                    break;
                }
                //에러
                else
                {
                    printf("올바르지 않은 입력입니다!\n");
                }
            }
            //관리자 수정 모드
            //차량 번호, 비밀번호, 정기차량 여부 수정 가능
            else if (n == 2)
            {
                //수정할 차량의 차량 번호를 입력 받음
                Palette des;
                int r = 0;
                if (IsParkingEmpty(parking))
                {
                    printf("수정할 차량이 존재하지 않습니다!\n");
                    continue;
                }
                printf("차량 번호 수정(1) 비밀번호 수정(2) 정기차량 수정(3) 종료(0): ");
                scanf("%d", &r);
                if (r == 1)
                {
                    printf("수정 대상(차량 번호): ");
                    scanf("%s", des.Car_id);
                    printf("수정 값(차량 번호): ");
                    scanf("%s", data.Car_id);
                    Admin_UpdatePalette(parking, des, data, 1);
                }
                else if (r == 2)
                {
                    printf("수정 대상(차량 번호): ");
                    scanf("%s", des.Car_id);
                    printf("수정 값(비밀번호): ");
                    scanf("%d", &data.Car_pw);
                    Admin_UpdatePalette(parking, des, data, 2);
                }
                //정기차량 수정은 기존에 정기차량이면 비정기차량으로, 비정기차량이면 정기차량으로 수정
                else if (r == 3)
                {
                    printf("수정 대상(차량 번호): ");
                    scanf("%s", des.Car_id);
                    Admin_UpdatePalette(parking, des, data, 3);
                }
                else if (r == 0)
                {
                    break;
                }
                else
                {
                    printf("올바르지 않은 입력입니다!\n");
                }
            }
            //종료
            else if (n == 0)
            {
                break;
            }
            //에러
            else
            {
                printf("올바르지 않은 입력입니다!\n");
            }
        }
        //사용자 모드
        else if (k == 2)
        {
            printf("사용자 모드: 입고(1) 검색(2) 수정(3) 출고(4) 종료(0): ");
            scanf("%d", &n);
            //사용자 입고
            if (n == 1)
            {
                if (IsParkingFull(parking))
                {
                    printf("주차 가능 공간이 없습니다!\n");
                    continue;
                }
                printf("사용자 이름: ");
                scanf("%s", data.Name);
                printf("차량 번호: ");
                scanf("%s", data.Car_id);
                printf("차량 높이(cm): ");
                scanf("%d", &data.Car_height);
                printf("차량 무게(kg): ");
                scanf("%d", &data.Car_weight);
                printf("차량 종류: ");
                scanf("%s", data.Car_type);
                printf("비밀번호(숫자): ");
                scanf("%d", &data.Car_pw);
                CreatePalette(parking, data);
            }
            //사용자 검색
            //사용자의 경우 관리자와 다르게 차량 비밀번호를 입력 받아 확인함
            else if (n == 2)
            {
                if (IsParkingEmpty(parking))
                {
                    printf("검색할 차량이 없습니다!\n");
                    continue;
                }
                printf("차량 번호: ");
                scanf("%s", data.Car_id);
                printf("비밀번호: ");
                scanf("%d", &data.Car_pw);
                RetrievePalette(parking, data);
            }
            //사용자 수정
            //사용자의 경우 관리자와 다르게 차량 비밀번호를 입력 받아 확인함
            //자신의 차량 번호와 비밀번호만 수정 가능
            else if (n == 3)
            {
                //수정할 차량의 차량 번호를 입력 받음
                Palette des;
                int r = 0;
                if (IsParkingEmpty(parking))
                {
                    printf("수정할 차량이 존재하지 않습니다!\n");
                    continue;
                }
                printf("차량 번호 수정(1) 비밀번호 수정(2) 종료(0): ");
                scanf("%d", &r);
                if (r == 1)
                {
                    printf("수정 대상(차량 번호): ");
                    scanf("%s", des.Car_id);
                    printf("수정 대상(차량 비밀번호): ");
                    scanf("%d", &des.Car_pw);
                    printf("수정 값(차량 번호): ");
                    scanf("%s", data.Car_id);
                    UpdatePalette(parking, des, data, 1);
                }
                else if (r == 2)
                {
                    printf("수정 대상(차량 번호): ");
                    scanf("%s", des.Car_id);
                    printf("수정 대상(차량 비밀번호): ");
                    scanf("%d", &des.Car_pw);
                    printf("수정 값(비밀번호): ");
                    scanf("%d", &data.Car_pw);
                    UpdatePalette(parking, des, data, 2);
                }
                else if (r == 0)
                {
                    break;
                }
                else
                {
                    printf("올바르지 않은 입력입니다!\n");
                }
            }
            //사용자 출고
            else if (n == 4)
            {
                if (IsParkingEmpty(parking))
                {
                    printf("출고할 차량이 없습니다!\n");
                    continue;
                }
                printf("차량 번호: ");
                scanf("%s", data.Car_id);
                printf("비밀번호: ");
                scanf("%d", &data.Car_pw);
                DeletePalette(parking, data);
            }
            //종료
            else if (n == 0)
            {
                break;
            }
            //에러
            else
            {
                printf("올바르지 않은 입력입니다!\n");
            }
        }
        //종료
        else if (k == 0)
        {
            break;
        }
        //에러
        else
        {
            printf("올바르지 않은 입력입니다!\n");
        }
    }

    //parking이 비어있는 상태에서 clear 실행하면, Incorrect checksum 오류 발생
    
    if (!IsParkingEmpty(parking))
    {
        Clear(parking);
    }
    
    return 0;
}

//각 층의 해쉬 테이블에 대해 더미노드 생성
void InitParking(Parking *parking)
{
    for (int i = 0; i < MAX_Height; i++)
    {
        //각 층에 있는 차의 개수를 0으로 설정
        parking->Car_num[i] = 0;
        //해쉬 테이블의 더미노드 생성

        for (int j = 0; j < MAX_Hash; j++)
        {
            parking->height[i][j] = (Palette *)malloc(sizeof(Palette));
            parking->height[i][j]->Next = NULL;
            
        }
    }
    
    for (int i = 0; i < MAX_Height; i++)
    {
        for (int j = 0; j < MAX_Hash; j++)
        {
            if(parking->height[i][j]->Next!=NULL){
                printf("오류 발생\n");
                while(parking->height[i][j]->Next!=NULL){
                    parking->height[i][j] = (Palette *)malloc(sizeof(Palette));
                    parking->height[i][j]->Next = NULL;
                }
            }
        }
    }
}

//동적할당된 더미노드 제거
void Clear(Parking *parking)
{
    for (int i = 0; i < MAX_Height; i++)
    {
        for (int j = 0; j < MAX_Hash; j++)
        {
            Palette *cur = parking->height[i][j];
            if (cur != NULL)
            {
                Palette *temp = cur;
                cur = cur->Next;
                free(temp);
            }
        }
    }
}

//해당 층이 모두 차있는지 검사
bool IsHeightFull(Parking *parking, int h)
{
    if (parking->Car_num[h] == MAX_Palette)
    {
        return true;
    }
    return false;
}

//해당 층이 모두 비었는지 검사
bool IsHeightEmpty(Parking *parking, int h)
{
    if (parking->Car_num[h] == 0)
    {
        return true;
    }
    return false;
}

//주차장이 모두 차있는지 검사
bool IsParkingFull(Parking *parking)
{
    //모든 층이 꽉 차있지 않으면 false
    for (int i = 0; i < MAX_Height; i++)
    {
        if (parking->Car_num[i] != MAX_Palette)
        {
            return false;
        }
    }
    return true;
}

//주차장이 모두 비었는지 검사
bool IsParkingEmpty(Parking *parking)
{
    //모든 층이 다 비어있지 않으면 false
    for (int i = 0; i < MAX_Height; i++)
    {
        if (parking->Car_num[i] != 0)
        {
            return false;
        }
    }
    return true;
}

//des에 data가 가진 값을 복사
void AddData(Palette *des, Palette data)
{
    strcpy(des->Name, data.Name);
    des->Car_weight = data.Car_weight;
    des->Car_height = data.Car_height;
    strcpy(des->Car_type, data.Car_type);
    strcpy(des->Car_id, data.Car_id);
    des->Car_pw = data.Car_pw;
    des->Next = NULL;
    des->time = time(NULL);
    //함수 추가 필요
    des->Is_regular = false;
}

//사용자 입고 함수
void CreatePalette(Parking *parking, Palette data)
{
    if (!CheckID(parking, data))
    {
        printf("차량번호가 올바르지 않습니다!\n");
        return;
    }
    for (int i = 0; i < MAX_Height; i++)
    {
        if (!IsHeightFull(parking, i))
        {
            //차량 번호 맨 앞자리를 해쉬 키로 설정
            int key = (data.Car_id[0] - '0') % MAX_Hash;
            Palette *temp = parking->height[i][key];
            //temp는 해쉬 테이블의 가장 마지막 노드를 가리킴
            while (temp->Next != NULL)
            {
                temp = temp->Next;
            }
            //새로운 값을 가지는 팔레트를 생성
            Palette *new = (Palette *)malloc(sizeof(Palette));
            AddData(new, data);
            //해당 팔레트를 해쉬 테이블에 연결
            temp->Next = new;
            parking->Car_num[i]++;
            printf("--------------입고 완료--------------\n");
            printf("입고 위치: -%d층, 남은 팔레트 개수: %d \n", i + 1, MAX_Palette - parking->Car_num[i]);
            printf("-------------------------------------\n");
            break;
        }
    }
}

//사용자 검색 함수
void RetrievePalette(Parking *parking, Palette data)
{
    for (int i = 0; i < MAX_Height; i++)
    {
        if (!IsHeightEmpty(parking, i))
        {
            int key = (data.Car_id[0] - '0') % MAX_Hash;
            Palette *temp = parking->height[i][key];
            //해쉬 테이블의 더미 노드 이후의 노드부터 마지막 노드까지 검사
            while (temp->Next != NULL)
            {
                temp = temp->Next;
                if (strcmp(temp->Car_id, data.Car_id) == 0)
                {
                    if (temp->Car_pw == data.Car_pw)
                    {
                        //검색이 완료되면 주차 시간과 비용 계산
                        time_t t = time(NULL);
                        int diff = difftime(t, temp->time);
                        int fee = Parkingfee(diff);
                        if (temp->Is_regular)
                        {
                            printf("----------------------검색 완료----------------------\n");
                            printf("사용자: %s 차량 번호: %s\n", temp->Name, temp->Car_id);
                            printf("차량 종류: %s 차량 높이: %dcm 차량 무게: %dkg\n", temp->Car_type, temp->Car_height, temp->Car_height);
                            printf("차량 위치: -%d층 주차 시간: %d분 정기주차 차량입니다!\n", i + 1, diff);
                            printf("-----------------------------------------------------\n");
                        }
                        else
                        {
                            printf("----------------------검색 완료----------------------\n");
                            printf("사용자: %s 차량 번호: %s\n", temp->Name, temp->Car_id);
                            printf("차량 종류: %s 차량 높이: %dcm 차량 무게: %dkg\n", temp->Car_type, temp->Car_height, temp->Car_height);
                            printf("차량 위치: -%d층 주차 시간: %d분 현재 주차 요금: %d원\n", i + 1, diff, fee);
                            printf("-----------------------------------------------------\n");
                        }
                        return;
                    }
                    else
                    {
                        printf("비밀번호 오류!\n");
                        return;
                    }
                }
            }
        }
    }
    printf("해당 차량이 존재하지 않습니다!\n");
}

//사용자 수정 함수
void UpdatePalette(Parking *parking, Palette des, Palette data, int type)
{
    //차량 번호 수정
    if (type == 1)
    {
        if (!CheckID(parking, data))
        {
            printf("수정할 차량번호가 올바르지 않습니다!\n");
            return;
        }
        for (int i = 0; i < MAX_Height; i++)
        {
            if (!IsHeightEmpty(parking, i))
            {
                int key = (des.Car_id[0] - '0') % MAX_Hash;
                Palette *temp = parking->height[i][key];
                while (temp->Next != NULL)
                {
                    //cur는 수정될 노드, temp는 cur의 이전 노드
                    Palette *cur = temp->Next;
                    if (strcmp(cur->Car_id, des.Car_id) == 0)
                    {
                        if (cur->Car_pw == des.Car_pw)
                        {
                            printf("------------차량 번호 수정 완료------------\n");
                            printf("이전 차량 번호: %s\n", cur->Car_id);
                            printf("변경 차량 번호: %s\n", data.Car_id);
                            printf("-------------------------------------------\n");

                            int new_key = (data.Car_id[0] - '0') % MAX_Hash;
                            //만일 기존의 차량 번호와 새로운 차량 번호의 해쉬 키가 같으면
                            //기존 차량 번호만 바꾸고 종료함
                            if (key == new_key)
                            {
                                strcpy(cur->Car_id, data.Car_id);
                                return;
                            }
                            //해시 테이블의 키를 차량 번호를 통해 설정했으므로 만약 해쉬 키가 다르면
                            //새로운 해시 테이블에 연결해야하기 때문에 새로운 해시 테이블 설정
                            Palette *new_hash = parking->height[i][new_key];
                            while (new_hash->Next != NULL)
                            {
                                new_hash = new_hash->Next;
                            }
                            //새로운 팔레트를 생성하고
                            //기존의 값과 새로운 차 번호 할당
                            Palette *new = malloc(sizeof(Palette));
                            AddData(new, *cur);
                            new->time = cur->time;
                            strcpy(new->Car_id, data.Car_id);

                            new_hash->Next = new;

                            //삭제할 노드의 이전노드와 다음 노드를 연결해주고 삭제 실행
                            temp->Next = cur->Next;
                            free(cur);
                            return;
                        }
                        else
                        {
                            printf("비밀번호 오류!\n");
                            return;
                        }
                    }
                    temp = temp->Next;
                }
            }
        }
    }
    //비밀번호 수정
    else if (type == 2)
    {
        for (int i = 0; i < MAX_Height; i++)
        {
            if (!IsHeightEmpty(parking, i))
            {
                int key = (des.Car_id[0] - '0') % MAX_Hash;
                Palette *temp = parking->height[i][key];
                //더미노드를 제외하고 검사하기 위함
                while (temp->Next != NULL)
                {
                    temp = temp->Next;
                    if (strcmp(temp->Car_id, des.Car_id) == 0)
                    {
                        if (temp->Car_pw == des.Car_pw)
                        {
                            printf("------------비밀번호 수정 완료------------\n");
                            printf("이전 비밀번호: %d\n", temp->Car_pw);
                            printf("변경 비밀번호: %d\n", data.Car_pw);
                            printf("------------------------------------------\n");
                            temp->Car_pw = data.Car_pw;
                            return;
                        }
                        else
                        {
                            printf("비밀번호 오류!\n");
                            return;
                        }
                    }
                }
            }
        }
    }
    printf("해당 차량이 존재하지 않습니다!\n");
}

//사용자 출고 함수
void DeletePalette(Parking *parking, Palette data)
{
    for (int i = 0; i < MAX_Height; i++)
    {
        if (!IsHeightEmpty(parking, i))
        {
            int key = (data.Car_id[0] - '0') % MAX_Hash;
            Palette *temp = parking->height[i][key];
            while (temp->Next != NULL)
            {
                //삭제 노드의 이전 노드와 다음 노드를 연결해야하기 때문에 생성
                //cur은 삭제될 노드를 의미
                Palette *cur = temp->Next;
                if (strcmp(cur->Car_id, data.Car_id) == 0)
                {
                    if (cur->Car_pw == data.Car_pw)
                    {
                        time_t t = time(NULL);
                        int diff = difftime(t, cur->time);
                        int fee = Parkingfee(diff);
                        if (cur->Is_regular)
                        {
                            printf("--------------출고 완료--------------\n");
                            printf("주차 시간: %d분\n", diff);
                            printf("정기차량 입니다!\n");
                            printf("-------------------------------------\n");
                        }
                        else
                        {
                            printf("--------------출고 완료--------------\n");
                            printf("주차 시간: %d분\n", diff);
                            printf("주차 요금: %d원\n", fee);
                            printf("-------------------------------------\n");
                        }
                        //삭제될 노드의 이전노드와 다음노드를 연결
                        temp->Next = cur->Next;
                        free(cur);
                        parking->Car_num[i]--;
                        return;
                    }
                    else
                    {
                        printf("비밀번호 오류!\n");
                        return;
                    }
                }
                temp = temp->Next;
            }
        }
    }
    printf("해당 차량이 존재하지 않습니다!\n");
}

//관리자 사용자 이름을 활용한 검색 함수
void Admin_RetrievePalette_User(Parking *parking, Palette data)
{
    // 해당 유저가 있었는지 검사하기 위한 변수(동명이인 처리 위함)
    int is_user = 0;
    //동명이인이 존재할 수 있기 때문에 반복문 계속 진행
    //원래 검색은 해쉬키를 이용하여 진행했지만, 사용자의 이름만 입력받기 때문에 모든 노드에 대해 검사 진행해야함
    for (int i = 0; i < MAX_Height; i++)
    {
        if (!IsHeightEmpty(parking, i))
        {
            for (int j = 0; j < MAX_Hash; j++)
            {
                Palette *temp = parking->height[i][j];
                while (temp->Next != NULL)
                {
                    temp = temp->Next;
                    if (strcmp(temp->Name, data.Name) == 0)
                    {
                        time_t t = time(NULL);
                        int diff = difftime(t, temp->time);
                        int fee = Parkingfee(diff);
                        printf("-------------------사용자 검색 완료-------------------\n");
                        printf("사용자: %s 차량 번호: %s 차량 비밀번호: %d\n", temp->Name, temp->Car_id, temp->Car_pw);
                        printf("차량 종류: %s 차량 높이: %dcm 차량 무게: %dkg\n", temp->Car_type, temp->Car_height, temp->Car_height);
                        if (temp->Is_regular)
                        {
                            printf("차량 위치: -%d층 주차 시간: %d분 정기주차 차량입니다!\n", i + 1, diff);
                        }
                        else
                        {
                            printf("차량 위치: -%d층 주차 시간: %d분 현재 주차 요금: %d원\n", i + 1, diff, fee);
                        }
                        printf("------------------------------------------------------\n");
                        is_user++;
                    }
                }
            }
        }
    }
    if (!is_user)
    {
        printf("해당 사용자가 존재하지 않습니다!\n");
    }
}

//관리자 차량 번호를 활용한 검색 함수
void Admin_RetrievePalette_Car(Parking *parking, Palette data)
{
    for (int i = 0; i < MAX_Height; i++)
    {
        if (!IsHeightEmpty(parking, i))
        {
            int key = (data.Car_id[0] - '0') % MAX_Hash;
            Palette *temp = parking->height[i][key];
            while (temp->Next != NULL)
            {
                temp = temp->Next;
                if (strcmp(temp->Car_id, data.Car_id) == 0)
                {
                    time_t t = time(NULL);
                    int diff = difftime(t, temp->time);
                    int fee = Parkingfee(diff);
                    printf("--------------------차량 검색 완료--------------------\n");
                    printf("사용자: %s 차량 번호: %s 차량 비밀번호: %d\n", temp->Name, temp->Car_id, temp->Car_pw);
                    printf("차량 종류: %s 차량 높이: %dcm 차량 무게: %dkg\n", temp->Car_type, temp->Car_height, temp->Car_height);
                    if (temp->Is_regular)
                    {
                        printf("차량 위치: -%d층 주차 시간: %d분 정기주차 차량입니다!\n", i + 1, diff);
                    }
                    else
                    {
                        printf("차량 위치: -%d층 주차 시간: %d분 현재 주차 요금: %d원\n", i + 1, diff, fee);
                    }
                    printf("------------------------------------------------------\n");
                    return;
                }
            }
        }
    }
    printf("해당 차량이 존재하지 않습니다!\n");
}

//관리자의 차량 정보 수정 함수
//des: 수정할 차량의 Car_id를 가짐, data: 변경하고자 하는 값을 가짐
void Admin_UpdatePalette(Parking *parking, Palette des, Palette data, int type)
{
    //차량 번호 수정
    if (type == 1)
    {
        if (!CheckID(parking, data))
        {
            printf("수정할 차량번호가 올바르지 않습니다!\n");
            return;
        }
        for (int i = 0; i < MAX_Height; i++)
        {
            if (!IsHeightEmpty(parking, i))
            {
                int key = (des.Car_id[0] - '0') % MAX_Hash;
                Palette *temp = parking->height[i][key];
                while (temp->Next != NULL)
                {
                    //차량 번호 수정의 경우 삭제가 일어날 수 있으므로 변수 할당
                    Palette *cur = temp->Next;
                    if (strcmp(cur->Car_id, des.Car_id) == 0)
                    {
                        printf("------------차량 번호 수정 완료------------\n");
                        printf("이전 차량 번호: %s\n", cur->Car_id);
                        printf("변경 차량 번호: %s\n", data.Car_id);
                        printf("-------------------------------------------\n");

                        int new_key = (data.Car_id[0] - '0') % MAX_Hash;
                        //만일 기존의 차량 번호와 새로운 차량 번호의 해쉬 키가 같으면
                        //기존 차량의 번호만 바꾸고 종료함
                        if (key == new_key)
                        {
                            strcpy(cur->Car_id, data.Car_id);
                            return;
                        }
                        //해시 테이블은 차량 번호를 통해 설정했으므로 만약 해쉬 키가 다르면
                        //새로운 해시 테이블에 연결해야하기 때문에 새로운 해시 테이블 설정
                        Palette *new_hash = parking->height[i][new_key];
                        while (new_hash->Next != NULL)
                        {
                            new_hash = new_hash->Next;
                        }
                        //새로운 팔레트를 생성하고
                        //기존의 값과 새로운 차 번호를 할당해줌
                        Palette *new = (Palette *)malloc(sizeof(Palette));
                        AddData(new, *cur);
                        new->time = cur->time;
                        strcpy(new->Car_id, data.Car_id);
                        new_hash->Next = new;

                        //삭제될 노드의 이전노드와 다음노드를 연결해줌
                        //기존의 노드는 삭제해줌
                        temp->Next = cur->Next;
                        free(cur);
                        return;
                    }
                    temp = temp->Next;
                }
            }
        }
    }
    //비밀번호 수정
    else if (type == 2)
    {
        for (int i = 0; i < MAX_Height; i++)
        {
            if (!IsHeightEmpty(parking, i))
            {
                int key = (des.Car_id[0] - '0') % MAX_Hash;
                Palette *temp = parking->height[i][key];
                //기존 노드의 삭제가 일어나지 않으므로 변수 할당 불필요
                while (temp->Next != NULL)
                {
                    temp = temp->Next;
                    if (strcmp(temp->Car_id, des.Car_id) == 0)
                    {
                        printf("------------비밀번호 수정 완료------------\n");
                        printf("이전 비밀번호: %d\n", temp->Car_pw);
                        printf("변경 비밀번호: %d\n", data.Car_pw);
                        printf("------------------------------------------\n");
                        temp->Car_pw = data.Car_pw;
                        return;
                    }
                }
            }
        }
    }
    //정기차량 유무 수정
    else
    {
        for (int i = 0; i < MAX_Height; i++)
        {
            if (!IsHeightEmpty(parking, i))
            {
                int key = (des.Car_id[0] - '0') % MAX_Hash;
                Palette *temp = parking->height[i][key];
                while (temp->Next != NULL)
                {
                    temp = temp->Next;
                    if (strcmp(temp->Car_id, des.Car_id) == 0)
                    {
                        if (temp->Is_regular)
                        {
                            temp->Is_regular = false;
                            printf("--------------정기차량 여부 수정 완료--------------\n");
                            printf("              정기차량 --> 비정기차량\n");
                            printf("--------------------------------------------------\n");
                        }
                        else
                        {
                            temp->Is_regular = true;
                            printf("--------------정기차량 여부 수정 완료--------------\n");
                            printf("              비정기차량 --> 정기차량\n");
                            printf("--------------------------------------------------\n");
                        }
                        return;
                    }
                }
            }
        }
    }
    printf("해당 차량이 존재하지 않습니다!\n");
}

//주차되어 있는 차량 정보 출력 함수
void PrintAll(Parking *parking)
{
    //층수 순서대로 출력, 같은 층이라면 번호판 앞자리에 따라 출력
    for (int i = 0; i < MAX_Height; i++)
    {
        if (!IsHeightEmpty(parking, i))
        {
            for (int j = 0; j < MAX_Hash; j++)
            {
                //i층의 j번째 해쉬테이블의 더미노드
                Palette *temp = parking->height[i][j];
                while (temp->Next != NULL)
                {
                    temp = temp->Next;
                    time_t t = time(NULL);
                    int diff = difftime(t, temp->time);
                    int fee = Parkingfee(diff);
                    printf("--------------------차량 검색 완료--------------------\n");
                    printf("사용자: %s 차량 번호: %s 차량 비밀번호: %d\n", temp->Name, temp->Car_id, temp->Car_pw);
                    printf("차량 종류: %s 차량 높이: %dcm 차량 무게: %dkg\n", temp->Car_type, temp->Car_height, temp->Car_height);
                    if (temp->Is_regular)
                    {
                        printf("차량 위치: -%d층 주차 시간: %d분 정기주차 차량입니다!\n", i + 1, diff);
                    }
                    else
                    {
                        printf("차량 위치: -%d층 주차 시간: %d분 현재 주차 요금: %d원\n", i + 1, diff, fee);
                    }
                    printf("------------------------------------------------------\n");
                }
            }
        }
    }
}

//시간에 따른 주차장 비용 계산 함수
int Parkingfee(int diff)
{
    int fee = Parking_fee * diff * 60;
    //1시간 이하 이용시 최소 요금 설정
    if (fee < Min_fee)
    {
        fee = Min_fee;
    }
    //1시간 이상 이용시
    else
    {
        // 추가요금은 60초 * 1초 요금 * 추가요금 단위(분)
        //60*Plus_unit 단위로 요금 추가됨
        int plus = 60 * Parking_fee * Plus_unit;
        fee = Min_fee + ((fee - Min_fee) / plus) * plus;
    }
    if (fee > Max_fee)
    {
        fee = Max_fee;
    }
    return fee;
}

//차량 번호가 존재하는지 검사하는 함수
bool CheckID(Parking *parking, Palette data)
{
    for (int i = 0; i < MAX_Height; i++)
    {
        if (!IsHeightEmpty(parking, i))
        {
            int key = (data.Car_id[0] - '0') % MAX_Hash;
            Palette *temp = parking->height[i][key];
            //id에 따른 해쉬 테이블을 참조하여 만약 동일한 차량 번호가 존재한다면 false 반환
            while (temp->Next != NULL)
            {
                temp = temp->Next;
                if (strcmp(temp->Car_id, data.Car_id) == 0)
                {
                    return false;
                }
            }
        }
    }
    return true;
}
