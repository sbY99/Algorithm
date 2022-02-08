#include <iostream>

using namespace std;
#define MAX 2187 + 1 //3의 7승 +1

int grid[MAX][MAX];
int N;
int r1, r2, r3; //-1,0,1의 개수

void divide(int start_x, int end_x, int start_y, int end_y)
{
    //비트마스킹으로 -1,0,1표시
    int temp = 0;
    bool corrected = true;

    for (int i = start_y; i <= end_y; i++)
    {
        for (int j = start_x; j <= end_x; j++)
        {
            if (grid[i][j] == -1)
            {
                if ((temp & 3) != 0)
                {
                    corrected = false;
                    break;
                }
                temp = 1 << 2;
            }
            else if (grid[i][j] == 0)
            {
                if ((temp & 5) != 0)
                {
                    corrected = false;
                    break;
                }
                temp = 1 << 1;
            }
            else
            {
                if ((temp & 6) != 0)
                {
                    corrected = false;
                    break;
                }
                temp = 1;
            }
        }
        if (corrected == false)
        {
            break;
        }
    }

    if (corrected == true)
    {
        //-1
        if (temp == 4)
        {
            r1 += (end_x - start_x + 1) * (end_x - start_x + 1);
        }
        //0
        else if (temp == 2)
        {
            r2 += (end_x - start_x + 1) * (end_x - start_x + 1);
        }
        //1
        else
        {
            r3 += (end_x - start_x + 1) * (end_x - start_x + 1);
        }
    }
    else
    {
        //10~18이면 2에 해당
        int diff = (end_x - start_x + 1) / 3 - 1;

        divide(start_x, start_x + diff, start_y, start_y + diff);
        divide(start_x, start_x + diff, start_y + diff + 1, start_y + diff + 2 * diff + 1);
        divide(start_x, start_x + diff, start_y + 2 * diff + 2, end_y);

        divide(start_x + diff + 1, start_x + diff * 2 + 1, start_y, start_y + diff);
        divide(start_x + diff + 1, start_x + diff * 2 + 1, start_y + diff + 1, start_y + diff + 2 * diff + 1);
        divide(start_x + diff + 1, start_x + diff * 2 + 1, start_y + 2 * diff + 2, end_y);

        divide(start_x + diff * 2 + 2, end_x, start_y, start_y + diff);
        divide(start_x + diff * 2 + 2, end_x, start_y + diff + 1, start_y + diff + 2 * diff + 1);
        divide(start_x + diff * 2 + 2, end_x, start_y + 2 * diff + 2, end_y);
    }
}

int main()
{
    cin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            scanf("%d", &grid[i][j]);
        }
    }
    divide(1, N, 1, N);
    printf("%d\n %d\n %d", r1, r2, r3);
}