#include <iostream>
#include <string>

using namespace std;
#define Max 64 + 1

int N;
int Grid[Max][Max];
string Result;

void divide(int start_x, int end_x, int start_y, int end_y)
{
    int is_One = 0;
    int is_Zero = 0;
    bool is_Okay = true;
    for (int i = start_x; i <= end_x; i++)
    {
        for (int j = start_y; j <= end_y; j++)
        {
            if (Grid[i][j] == 1)
            {
                if (is_Zero == 1)
                {
                    is_Okay = false;
                    break;
                }
                is_One = 1;
            }
            if (Grid[i][j] == 0)
            {
                if (is_One == 1)
                {
                    is_Okay = false;
                    break;
                }
                is_Zero = 1;
            }
        }
    }
    if (is_Okay)
    {
        if (is_One)
            Result += "1";

        else
            Result += "0";
    }
    else
    {
        int mid_x = (start_x + end_x) / 2;
        int mid_y = (start_y + end_y) / 2;
        Result += "(";
        divide(start_x, mid_x, start_y, mid_y);
        divide(start_x, mid_x, mid_y + 1, end_y);
        divide(mid_x + 1, end_x, start_y, mid_y);
        divide(mid_x + 1, end_x, mid_y + 1, end_y);
        Result += ")";
    }
}

int main()
{
    scanf("%d", &N);
    getchar();
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            char input;
            scanf("%c", &input);
            Grid[i][j] = input - '0';
        }
        getchar();
    }
    divide(1, N, 1, N);
    cout << Result;
}