#include <iostream>

using namespace std;

int grid[129][129];
int blue_count;  //1
int white_count; //0

void func(int start_x, int end_x, int start_y, int end_y)
{
    if (start_x == end_x)
    {
        if (grid[start_y][start_x] == 0)
        {
            white_count++;
        }
        else
        {
            blue_count++;
        }
        return;
    }

    //white로 전부 채워져있는지 검사
    int white_check = 0;
    int blue_check = 0;
    for (int i = start_y; i <= end_y; i++)
    {
        for (int j = start_x; j <= end_x; j++)
        {
            if (grid[i][j] != 0)
            {
                white_check++;
                break;
            }
        }
    }
    //blue로 전부 채워져있는지 검사
    for (int i = start_y; i <= end_y; i++)
    {
        for (int j = start_x; j <= end_x; j++)
        {
            if (grid[i][j] != 1)
            {
                blue_check++;
                break;
            }
        }
    }
    //white_check이 0이면 모두 하얀색으로 채워짐
    //blue_check이 0이면 모두 파란 색으로 채워짐
    if (white_check == 0)
    {
        white_count++;
        return;
    }
    else if (blue_check == 0)
    {
        blue_count++;
        return;
    }
    else
    {
        //둘다 아닐 경우 4등분하여 재귀 호출
        int mid_x = (start_x + end_x) / 2;
        int mid_y = (start_y + end_y) / 2;
        func(start_x, mid_x, start_y, mid_y);
        func(mid_x + 1, end_x, start_y, mid_y);
        func(start_x, mid_x, mid_y + 1, end_y);
        func(mid_x + 1, end_x, mid_y + 1, end_y);
    }
}

int main()
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            scanf("%d", &grid[i][j]);
        }
    }

    func(1, N, 1, N);
    printf("%d\n", white_count);
    printf("%d", blue_count);
    return 0;
}