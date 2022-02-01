#include <iostream>
#include <algorithm>

using namespace std;

int N;
int Result;

int Stair[5][301];

int main()
{
    cin >> N;
    int input1;
    int input2;
    int input3;

    //초기 예외 처리
    cin >> input1;
    if (N == 1)
    {
        printf("%d", input1);
        return 0;
    }
    cin >> input2;
    if (N == 2)
    {
        printf("%d", input1 + input2);
        return 0;
    }
    cin >> input3;
    if (N == 3)
    {
        printf("%d", max(input1 + input2, (max(input1 + input3, input2 + input3))));
        return 0;
    }

    //각각 OXO, OOX, XOO, XOX
    Stair[1][1] = input1;
    Stair[1][3] = input1 + input3;

    Stair[2][1] = input1;
    Stair[2][2] = input1 + input2;

    Stair[3][2] = input2;
    Stair[3][3] = input2 + input3;

    Stair[4][1] = input2;

    int input;
    for (int i = 4; i <= N; i++)
    {
        cin >> input;
        for (int j = 1; j <= 4; j++)
        {
            //j행이 OXO 라면 다음은 O or X
            //즉, XOO or XOX
            if (j == 1)
            {
                Stair[3][i] = Stair[1][i - 1] + input;
                Stair[4][i - 1] = Stair[1][i - 1];
            }
            //j행이 OOX 라면 다음은 O
            //즉, OXO
            if (j == 2)
            {
                Stair[1][i] = Stair[2][i - 2] + input;
            }
            //j행이 XOO 라면 다음은 X
            //즉, OOX
            if (j == 3)
            {
                Stair[2][i - 1] = Stair[3][i - 1];
            }
            //j행이 XOX 라면 다음은 O
            //즉, OXO
            if (j == 4)
            {
                Stair[1][i] = max(Stair[1][i], Stair[4][i - 2] + input);
            }
        }
    }

    for (int i = 1; i <= 4; i++)
    {
        if (Result < Stair[i][N])
        {
            Result = Stair[i][N];
        }
    }
    printf("%d", Result);
    return 0;
}
