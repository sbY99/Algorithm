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


typedef enum _admin_or_user{
    ADMIN = 1,
    USER = 2,
    Quit = 0
}admin_or_user;

typedef enum _CRUD{
    CREATE = 1,
    RETRIEVE = 2,
    UPDATE = 3,
    DELETE = 4,
    QUIT = 0
}CRUD;


//저장되는 차량 정보들
typedef struct _palette
{
    bool Is_regular;
    char Name[20];
    char Car_type[20];
    int Car_weight;
    int Car_height;
    char Car_id[11];
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

//차량번호의 한글과 숫자를 분리한 구조체
typedef struct _car_id_form{
    int Key;
    char Korean[4];
}car_id_form;

//AVL트리 노드
typedef struct _regular_car_node{
    struct _regular_car_node* leftchild;
    car_id_form ID;
    char Name[20];
    char phone_num[12];
    int Car_pw;
    char Car_type[20];
    int height_diff;
    struct _regular_car_node* rightchild;
}regular_car_node;

//AVL 트리
typedef struct _regular_cars_AVL_tree{
    regular_car_node* root;
    int numberOfRegularCars;
}regular_cars_AVL_tree;


 
void InitParking(Parking *parking);
bool IsHeightFull(Parking *parking, int h);
bool IsHeightEmpty(Parking *parking, int h);
bool IsParkingFull(Parking *parking);
bool IsParkingEmpty(Parking *parking);
void AddData(Palette *des, Palette data, bool is_regular);
void Clear(Parking *parking);
 
void CreatePalette(Parking *parking, Palette data, bool is_regular);
void RetrievePalette(Parking *parking, Palette data);
void UpdatePalette(Parking *parking, Palette des, Palette data, int type);
void DeletePalette(Parking *parking, Palette data);
 
void Admin_RetrievePalette_User(Parking *parking, Palette data);
void Admin_RetrievePalette_Car(Parking *parking, Palette data);
void Admin_UpdatePalette(Parking *parking, Palette des, Palette data, int type);
 
void PrintAll(Parking *parking);
int Parkingfee(int diff);
bool CheckID(Parking *parking, Palette data);



void InitAVLTree(regular_cars_AVL_tree* regular_cars);
void AVLTreeOperation(regular_cars_AVL_tree* regular_cars, CRUD crud, Parking *parking, Palette data);

car_id_form SaparateCarID(char* Car_id);

void CreateRegular(regular_cars_AVL_tree* regular_cars, Parking* parking, Palette data);
bool* RetrieveRegular(regular_cars_AVL_tree* regular_cars, Palette* data, bool check_pw);
bool UpdateRegular(regular_cars_AVL_tree* regular_cars, Parking* parking, Palette* des, Palette data);
void DeleteRegular(regular_cars_AVL_tree* regular_cars, Parking* parking);
void UpdateIsRegular(Parking* parking, char* car_id_str, bool to_regular);

void searchAndRepairAfterInsertion(regular_cars_AVL_tree* regular_cars, regular_car_node* inserted_node);
int get_height(regular_car_node* node);
int get_height_diff(regular_car_node* node);
    
int main()
{
    Parking *parking = (Parking *)malloc(sizeof(parking));
    InitParking(parking);
    regular_cars_AVL_tree _regular_cars;
    regular_cars_AVL_tree* regular_cars = &_regular_cars;
    InitAVLTree(regular_cars);
    CRUD crud;
    admin_or_user Admin_Or_User;
    while (1)
    {
        //입력 받는 차량 정보
        Palette data;
        printf("관리자 모드(1) 사용자 모드(2) 종료(0): ");
        scanf("%d", (int*)&Admin_Or_User);
        //관리자 모드
        if (Admin_Or_User == ADMIN)
        {
        int options_in_admin_mode;
        printf("관리자 모드: 정기차량관리(1) 입고된차량관리(2) 종료(0): ");
        scanf("%d",&options_in_admin_mode);
        if(options_in_admin_mode == 1){
             printf("정기차량관리: 등록(1) 검색(2) 수정(3) 등록해제(4) 종료(0): ");
            
            scanf("%d",(int*)&crud);
            if(crud == QUIT) break;
            AVLTreeOperation(regular_cars, crud, parking, data);
        }
        else if(options_in_admin_mode == 0){
            break;
        }
        else{


            printf("관리자 모드: 검색(1) 수정(2) 종료(0): ");
            scanf("%d",(int*)&crud);
        //종료
        if(crud == Quit){
        break;
        }
        crud++;
            //관리자 검색 모드
        if (crud == RETRIEVE)
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
            else if (crud == UPDATE)
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
            UpdateRegular(regular_cars, parking,&des,data);
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
           //에러
            else
            {
                printf("올바르지 않은 입력입니다!\n");
            }
        }
        }
        //사용자 모드
        else if (Admin_Or_User == USER)
        {
            printf("사용자 모드: 입고(1) 검색(2) 수정(3) 출고(4) 종료(0): ");
            scanf("%d", (int*)&crud);
            //사용자 입고
            if (crud == CREATE)
            {
                if (IsParkingFull(parking))
                {
                    printf("주차 가능 공간이 없습니다!\n");
                    continue;
                }
                printf("차량 번호: ");
                scanf("%s", data.Car_id);
    
    //    printf("is_regular: %d", data.Is_regular);
        bool* check_regular = RetrieveRegular(regular_cars, &data, true);
        if(check_regular[0]){
            if(check_regular[1] == false){
                puts("비밀번호 오류");
                continue;
            }
            data.Is_regular = true;
        }
        else{
            printf("사용자 이름: ");
                       scanf("%s", data.Name);
                       printf("비밀번호(숫자4자리): ");
                       scanf("%d", &data.Car_pw);
            printf("차량 종류: ");
                       scanf("%s", data.Car_type);
                
        }
        free(check_regular);
        printf("차량 높이(cm): ");
                scanf("%d", &data.Car_height);
                printf("차량 무게(kg): ");
                scanf("%d", &data.Car_weight);
                CreatePalette(parking, data, data.Is_regular);
        data.Is_regular = 0;
            }
            //사용자 검색
            //사용자의 경우 관리자와 다르게 차량 비밀번호를 입력 받아 확인함
            else if (crud == RETRIEVE)
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
            else if (crud == UPDATE)
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
            UpdateRegular(regular_cars,parking, &des, data);
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
            else if (crud == DELETE)
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
            else if (crud == QUIT)
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
        else if (Admin_Or_User == Quit)
        {
            break;
        }
        //에러
        else
        {
            printf("올바르지 않은 입력입니다!\n");
        }
    }
   
    Clear(parking);
   
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
            parking->height[i][j]->Car_pw=0;
        }
    }
   
    //첫 할당때 할당되지 않는 메모리 오류를 고치기 위함
    for (int i = 0; i < MAX_Height; i++)
    {
        for (int j = 0; j < MAX_Hash; j++)
        {
            if(parking->height[i][j]->Next!=NULL){
                while(parking->height[i][j]->Next!=NULL){
                    parking->height[i][j] = (Palette *)malloc(sizeof(Palette));
                    parking->height[i][j]->Next = NULL;
                    
                    parking->height[i][j]->Car_pw = 1;
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
            //코어 덤프 오류 잡기 위함
            if(cur->Car_pw!=0) continue;
            if (cur != NULL)
            {
                Palette *temp = cur;
                cur = cur->Next;
                free(temp);
            }
        }
    }
   
}


void InitAVLTree(regular_cars_AVL_tree* regular_cars){
    regular_cars->numberOfRegularCars = 0;
    regular_cars->root = NULL;
}
void AVLTreeOperation(regular_cars_AVL_tree* regular_cars, CRUD crud, Parking *parking, Palette data){
    switch(crud){

        case CREATE:
            CreateRegular(regular_cars, parking, data);
            return;

        case RETRIEVE:
            if(!(RetrieveRegular(regular_cars, &data , false)[0])) puts("정기등록차량이 아닙니다");
            return;
        
        case UPDATE:
            UpdateRegular(regular_cars, parking, NULL, data);
            return;

        case DELETE:
            DeleteRegular(regular_cars, parking);
            return;
        case QUIT:
            exit(0);
            return;
        default:
            puts("올바르지 않은 입력입니다.");
            return;

    }

}
//정기차량 등록
//입고되지 않은 차량번호 -> 그냥 등록하면 됨.
//입고돼있는 차량번호 -> 팔레트에 접근하여 이름, 비밀번호, 차량종류등 최신화.
void CreateRegular(regular_cars_AVL_tree* regular_cars, Parking* parking, Palette data){
    regular_car_node* newnode, *current, *parent;
    char id_input_str[10];
    car_id_form id_input;
    Palette palette_new_info;

    newnode = (regular_car_node*)malloc(sizeof(regular_car_node));
    printf("사용자 이름: ");
    scanf("%s", newnode->Name);
    strcpy(palette_new_info.Name, newnode->Name);
    printf("차량 번호: ");
    scanf("%s", id_input_str);
    strcpy(palette_new_info.Car_id,id_input_str);
    newnode->ID = SaparateCarID(id_input_str);
    printf("전화번호: ");
    scanf("%s", newnode->phone_num);
    printf("차종: ");
    scanf("%s", newnode->Car_type);
    strcpy(palette_new_info.Car_type, newnode->Car_type);
    printf("비밀번호(숫자4자리): ");
    scanf("%d",&newnode->Car_pw);
    palette_new_info.Car_pw = newnode->Car_pw;
    newnode->height_diff = 0;
    if(regular_cars->root == NULL){
        regular_cars->root = newnode;
        regular_cars->numberOfRegularCars++;
        Admin_UpdatePalette(parking, data, palette_new_info, 4);
        UpdateIsRegular(parking, id_input_str, true);
        
        return ;
    }

    current = regular_cars->root;
    parent = NULL;

    while(1){



        //입력된 키값이 더 큰 경우->오른쪽으로
        if(current->ID.Key < newnode->ID.Key){
            if(current->rightchild != NULL){
                parent = current;
                current = current->rightchild;
                continue;
            }
            else{
                current->rightchild = newnode;
                regular_cars->numberOfRegularCars++;
                Admin_UpdatePalette(parking, data ,palette_new_info, 4);
                UpdateIsRegular(parking, id_input_str, true);
                return;
            }
        }
        //입력된 키값이 더 작은경우-> 왼쪽으로
        else if(current->ID.Key > newnode->ID.Key){
            if(current->leftchild != NULL){
                parent = current;
                current = current->leftchild;
                continue;
            }
            else{
                current->leftchild = newnode;
                regular_cars->numberOfRegularCars++;
                Admin_UpdatePalette(parking, data ,palette_new_info, 4);
                
                UpdateIsRegular(parking, id_input_str, true);
                return;
            }
        }
        //입력된 키값이 동일한경우 -> 한국어부분 비교
        else{
            if(strncmp(current->ID.Korean,newnode->ID.Korean,sizeof("가")-1) < 0){
                if(current->rightchild != NULL){
                    parent = current;
                    current = current->rightchild;
                    continue;
                }
                else{
                    current->rightchild = newnode;
                    regular_cars->numberOfRegularCars++;
                    Admin_UpdatePalette(parking, data ,palette_new_info,  4);
                UpdateIsRegular(parking, id_input_str, true);
                    return;
                }
            }
            else if(strncmp(current->ID.Korean,newnode->ID.Korean,sizeof("가")-1) > 0){
                if(current->leftchild != NULL){
                    parent = current;
                    current = current->leftchild;
                    continue;
                }
                else{
                    current->leftchild = newnode;
                    regular_cars->numberOfRegularCars++;
                    Admin_UpdatePalette(parking, data ,palette_new_info, 4);
                UpdateIsRegular(parking, id_input_str, true);
                    return;
                }

            }
            else{
                puts("차량번호가 동일한 값이 이미 존재합니다.");
                free(newnode);
                return;
            }
        }
    }

}

bool* RetrieveRegular(regular_cars_AVL_tree* regular_cars, Palette* data, bool check_pw){
    regular_car_node *current ;
    char id_input_str[10];
    car_id_form id_input;
    //0번째 인덱스는 정기차량인지 여부 확인, 1번째 인덱스는 비밀번호가 맞는지 확인
    bool* result = (bool*)calloc(2,sizeof(bool));

    if(check_pw == false){
        printf("검색 대상(차량 번호): ");
        scanf("%s", id_input_str);
        id_input = SaparateCarID(id_input_str);
    }
    else{
        id_input = SaparateCarID(data->Car_id);
    }
    if(regular_cars->root == NULL){
        result[0] = false;
        result[1] = false;
        return result;
    }

    current = regular_cars->root;
    
    while(1){
        //입력된 키값이 더 큰 경우->오른쪽으로
        if(current->ID.Key < id_input.Key){
            if(current->rightchild != NULL){
                current = current->rightchild;
                continue;
            }
            else{
                result[0] = false;
                result[1] = false;
                return result;
            }
        }
        //입력된 키값이 더 작은경우-> 왼쪽으로
        else if(current->ID.Key > id_input.Key){
            if(current->leftchild != NULL){
                current = current->leftchild;
                continue;
            }
            else{
                result[0] = false;
                result[1] = false;
                return result;
            }
        }
        //입력된 키값이 동일한경우 -> 한국어부분 비교
        else{
            if(strncmp(current->ID.Korean,id_input.Korean,sizeof("가")-1) < 0){
                if(current->rightchild != NULL){
                    current = current->rightchild;
                    continue;
                }
                else{
                    result[0] = false;
                    result[1] = false;
                    return result;
                }
            }
            else if(strncmp(current->ID.Korean, id_input.Korean,sizeof("가")-1) > 0){
                if(current->leftchild != NULL){
                    continue;
                }
                else{
                    result[0]=false;
                    result[1] = false;
                    return result;
                }

            }
            else{
                result[0] = true;
                if(check_pw == false){
                    printf("--------------------차량 검색 완료--------------------\n");
                                printf("사용자: %s 차량 비밀번호: %d\n", current->Name, current->Car_pw);
                                printf("전화번호: %s\n", current->phone_num);
                                printf("------------------------------------------------------\n");
                }
                if(check_pw==true){
                    puts("정기차량입니다!");
                    int checking_pw;
                    printf("정기회원 비밀번호(숫자4자리): ");
                    scanf("%d",&checking_pw);
                    if(checking_pw == current->Car_pw) {
                        
                        result[1] = true;
                        strcpy(data->Car_type, current->Car_type);
                        strcpy(data->Name , current->Name);
                        data->Car_pw = checking_pw;
                    }
                    else result[1] = false;
                }
                else result[1] = false;
            return result;
            }

        }
    }
}

bool UpdateRegular(regular_cars_AVL_tree* regular_cars, Parking* parking, Palette* des, Palette data){
    regular_car_node *current;
    char id_input_str[10];
    car_id_form id_input;
    
    if(des == NULL){
        printf("수정 대상(차량 번호): ");
        scanf("%s", id_input_str);
        id_input = SaparateCarID(id_input_str);
    }
    else{
        id_input = SaparateCarID(des->Car_id);
    }
    
    if(regular_cars->root == NULL){
        puts("차량번호가 일치하는 차량이 없습니다!");
        return false;
    }

    current = regular_cars->root;
    
    while(1){
        //입력된 키값이 더 큰 경우->오른쪽으로
        if(current->ID.Key < id_input.Key){
            if(current->rightchild != NULL){
                current = current->rightchild;
                continue;
            }
            else{
                puts("차량번호가 일치하는 차량이 없습니다!");
        
                return false;
            }
        }
        //입력된 키값이 더 작은경우-> 왼쪽으로
        else if(current->ID.Key > id_input.Key){
            if(current->leftchild != NULL){
                current = current->leftchild;
                continue;
            }
            else{
                puts("차량번호가 일치하는 차량이 없습니다!");
                return false;
            }
        }
        //입력된 키값이 동일한경우 -> 한국어부분 비교
        else{
            if(strncmp(current->ID.Korean,id_input.Korean,sizeof("가")-1) < 0){
                if(current->rightchild != NULL){
                    current = current->rightchild;
                    continue;
                }
                else{
                    puts("차량번호가 일치하는 차량이 없습니다!");
                    return false;
                }
            }
            else if(strncmp(current->ID.Korean, id_input.Korean, sizeof("가")-1) > 0){
                if(current->leftchild != NULL){
                    current = current->leftchild;
                    continue;
                }
                else{
                    puts("차량번호가 일치하는 차량이 없습니다!");
                     return false;
                }

            }
            else{
                Palette palette_new_info;
                if(des == NULL){
                    printf("사용자 이름: ");
                    scanf("%s", current->Name);
                    strcpy(palette_new_info.Name, current->Name);

                    printf("전화번호: ");
                    scanf("%s", current->phone_num);
                    
                    printf("차량종류: ");
                    scanf("%s", current->Car_type);
                    strcpy(palette_new_info.Car_type ,current->Car_type);
                    
                    printf("비밀번호(숫자4자리): ");
                    scanf("%d",&current->Car_pw);
                    palette_new_info.Car_pw = current->Car_pw;
                
                    Admin_UpdatePalette(parking, data, palette_new_info, 4);

                }
                else{
                    current->Car_pw = data.Car_pw;
                }
            
                            
                puts("수정완료");
                return true;
            }
        }
    }
}
void DeleteRegular(regular_cars_AVL_tree* regular_cars, Parking* parking){
    regular_car_node *current, *parent;
    char id_input_str[10];
    car_id_form id_input;

    if(regular_cars->numberOfRegularCars != -1){

    printf("차량 번호: ");
    scanf("%s", id_input_str);
    id_input = SaparateCarID(id_input_str);
    }
    else{
        id_input.Key = regular_cars->root->ID.Key;
        strcpy(id_input.Korean ,regular_cars->root->ID.Korean);
        printf("subtree key: %d, korean: ", id_input.Key);
        puts(id_input.Korean);
    }
    if(regular_cars->root == NULL){
        puts("삭제할 데이터가 존재하지 않습니다.");
        return;
    }

    current = regular_cars->root;
    parent = NULL;

    
    while(1){
        //입력된 키값이 더 큰 경우->오른쪽으로
        if(current->ID.Key < id_input.Key){
            if(current->rightchild != NULL){
                parent = current;
                current = current->rightchild;
                puts("삭제 완료");
                continue;
            }
            else{
                puts("입력한 번호와 일치하는 차량번호가 없습니다.");
                return;
            }
        }
        //입력된 키값이 더 작은경우-> 왼쪽으로
        else if(current->ID.Key > id_input.Key){
            if(current->leftchild != NULL){
                parent = current;
                current = current->leftchild;
                continue;
            }
            else{
                puts("입력한 번호와 일치하는 차량번호가 없습니다.");
                return;
            }
        }
        //입력된 키값이 동일한경우 -> 한국어부분 비교
        else{
            if(strncmp(current->ID.Korean, id_input.Korean, sizeof("가")-1) < 0){
                if(current->rightchild != NULL){
                    parent = current;
                    current = current->rightchild;
                    continue;
                }
                else{
                    puts("입력한 번호와 일치하는 차량번호가 없습니다.");
                    return;
                }
            }
            else if(strncmp(current->ID.Korean, id_input.Korean, sizeof("가")-1) > 0){
                if(current->leftchild != NULL){
                    parent = current;
                    current = current->leftchild;
                    continue;
                }
                else{
                    puts("입력한 번호와 일치하는 차량번호가 없습니다.");
                    return;
                }

            }
            //번호일치하는 차량 발견! --> 삭제하기.
            else{
                //자식노드가 없는 경우
                if(current->leftchild == NULL && current->rightchild==NULL){
                    //루트노드 삭제하는 경우
                    if(parent == NULL){
                        regular_cars->root = NULL;
                        free(current);
                        regular_cars->numberOfRegularCars--;
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                    else if(parent->leftchild == current){
                        parent->leftchild = NULL;
                        regular_cars->numberOfRegularCars--;
                        free(current);
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                    else if(parent->rightchild == current){
                        parent->rightchild = NULL;
                        regular_cars->numberOfRegularCars--;
                        free(current);
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                    
                }
                //왼쪽 자식노드만 있는 경우
                else if(current->leftchild != NULL && current->rightchild == NULL){
                    if(parent == NULL){
                        regular_cars->root = current->leftchild;
                        regular_cars->numberOfRegularCars--;
                        free(current);
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                    else if(parent->leftchild == current){
                        parent->leftchild = current->leftchild;
                        regular_cars->numberOfRegularCars--;
                        free(current);
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                    else if(parent->rightchild == current){
                        parent->rightchild = current->leftchild;
                        regular_cars->numberOfRegularCars--;
                        free(current);
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                }
                
                //오른쪽 자식노드만 있는 경우
                else if(current->leftchild == NULL && current->rightchild != NULL){
                    if(parent == NULL){
                        regular_cars->root = current->rightchild;
                        regular_cars->numberOfRegularCars--;
                        free(current);
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                    else if(parent->leftchild == current){
                        parent->leftchild = current->rightchild;
                        regular_cars->numberOfRegularCars--;
                        free(current);
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                    else if(parent->rightchild == current){
                        parent->rightchild = current->rightchild;
                        regular_cars->numberOfRegularCars--;
                        free(current);
                        UpdateIsRegular(parking, id_input_str, false);
                        puts("삭제 완료");
                        return;
                    }
                }
                //양쪽 모두 자식노드가 있는경우
                else{
                    regular_car_node* target, *target_parent;
                    
                    target = current->rightchild;
                    target_parent = current;
                    
                    while(target->leftchild != NULL){
                        target_parent = target;
                        target = target->leftchild;
                    }

                    if(parent == NULL){
                        regular_cars->root = target;
                    }

                    else if(parent->leftchild == current){
                        parent->leftchild = target;
                    }
                    else if(parent->rightchild == current){
                        parent->rightchild = target;
                    }

                    if(target_parent->leftchild == target){
                        target_parent->leftchild = target->rightchild;
                    }
                    else if(target_parent->rightchild == target){
                        target_parent->rightchild = target->rightchild;
                    }

                    target->leftchild = current->leftchild;
                    target->rightchild = current->rightchild;

                    free(current);
                    UpdateIsRegular(parking, id_input_str, false);
                        

                    return;
                }
            }
        }
    }
}

int get_height(regular_car_node* node){
    if(node->leftchild == NULL && node->rightchild == NULL) return 1;
    else if(node->leftchild == NULL && node->rightchild != NULL) return 1+get_height(node->rightchild);
    else if(node->leftchild != NULL && node->rightchild == NULL) return 1+get_height(node->leftchild);
    else{
        int l = get_height(node->leftchild);
        int r = get_height(node->rightchild);
        
        if(l<r) return r+1;
        else return l+1;
    }
}
int get_height_diff(regular_car_node* node){
    if(node->leftchild == NULL && node->rightchild == NULL) return 0;
    else if(node->leftchild == NULL && node->rightchild != NULL) return 0-get_height(node->rightchild);
    else if(node->leftchild != NULL && node->rightchild == NULL) return get_height(node->leftchild);
    else{
        int l = get_height(node->leftchild);
        int r = get_height(node->rightchild);
        
        return l-r;
    
    }
}
/*
regular_car_node* search_lowest_inbalaced(regular_cars_AVL_tree* regular_cars, regular_car_node* inserted_node){
    regular_car_node* imbalanced = malloc(sizeof(regular_car_node));
    regular_car_node* current = regular_cars->root;

    while(1){
        int diff = get_height_diff(current);
        if(diff>=-1 && diff<=1) {
            if(inserted_node->ID.Key > current->ID.Key) regular
        }


    }

}*/

void searchAndRepairAfterInsertion(regular_cars_AVL_tree* regular_cars, regular_car_node* inserted_node){
//    inserted_node->ID.Key




}


//차량번호의 숫자부분과 한국어부분을 쪼개는 함수
car_id_form SaparateCarID(char* id_input_str){
    int AVL_key=0;
    int i=0;
    int KoreanCharacterSize = sizeof("가")-1;
    car_id_form result;

    int len = strlen(id_input_str) - KoreanCharacterSize;
    //printf("차량번호길이: %d\n", len);
    for(i=0;i<len;i++){
    
        AVL_key *= 10;
        if(i<len-4){
            AVL_key += id_input_str[i] - '0';
        }
        else{
            AVL_key += id_input_str[i+KoreanCharacterSize]-'0';
        }
    }

    result.Key = AVL_key;
    //printf("resultKey: %d\n", result.Key);
    strncpy(result.Korean, id_input_str+2, KoreanCharacterSize);
    return result;

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
void AddData(Palette *des, Palette data, bool is_regular)
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
    if(is_regular) des->Is_regular = true;
    else des->Is_regular = false;
}
 
//사용자 입고 함수
void CreatePalette(Parking *parking, Palette data, bool is_regular)
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
            AddData(new, data, is_regular);
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
                            AddData(new, *cur , data.Is_regular);
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
                        AddData(new, *cur, data.Is_regular);
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
    else if(type == 3)
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
    if(type !=4) printf("해당 차량이 존재하지 않습니다!\n");
           if(type == 4){
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
                        temp->Car_pw = data.Car_pw;
                        strcpy(temp->Car_type , data.Car_type);
                        strcpy(temp->Name , data.Name);
                        return;
                        }
                      }
                }
          }
        }
}

void UpdateIsRegular(Parking* parking, char* car_id_str, bool to_regular){
    for (int i = 0; i < MAX_Height; i++)
        {
            if (!IsHeightEmpty(parking, i))
            {
                int key = (car_id_str[0] - '0') % MAX_Hash;
                Palette *temp = parking->height[i][key];
                while (temp->Next != NULL)
                {
                    temp = temp->Next;
                    if (strcmp(temp->Car_id, car_id_str) == 0)
                    {
                        if (!to_regular)
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
