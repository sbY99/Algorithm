#include <iostream>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int T, N;
int Size;
bool reverse_check;
bool err_check;
deque<int> dq;
string p;

void init();
void input();
void solve();
void print();

void init()
{
    Size = 0;
    p = "";
    err_check = false;
    reverse_check = false;
    dq.clear();
}

void input()
{
    cin >> p;
    cin >> N;

    string input;
    cin >> input;

    int temp = N;
    int num = 0;
    int idx = 1;
    while (temp != 0)
    {
        //문자 -> 저장된 숫자 push
        if (input[idx] == ',' || input[idx] == ']')
        {
            dq.push_back(num);
            num = 0;
            idx++;
            temp--;
        }
        //숫자 -> 숫자값 갱신
        else
        {
            num = num * 10 + input[idx] - '0';
            idx++;
        }
    }
}

void solve()
{
    Size = N;
    for (int i = 0; i < p.size(); i++)
    {
        if (p[i] == 'R')
        {
            if (reverse_check == true)
                reverse_check = false;
            else
                reverse_check = true;
        }
        if (p[i] == 'D')
        {
            if (Size == 0)
            {
                err_check = true;
                break;
            }
            else
            {
                if (reverse_check == false)
                    dq.pop_front();
                else
                    dq.pop_back();
                Size--;
            }
        }
    }
}

void print()
{
    if (err_check == true)
    {
        printf("error\n");
    }
    else
    {
        printf("[");
        if (reverse_check == false)
        {
            for (int j = 0; j < dq.size(); j++)
            {
                printf("%d", dq[j]);
                if (j != dq.size() - 1)
                {
                    printf(",");
                }
            }
        }
        else
        {
            for (int j = dq.size() - 1; j >= 0; j--)
            {
                printf("%d", dq[j]);
                if (j != 0)
                {
                    printf(",");
                }
            }
        }
        printf("]");
        printf("\n");
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> T;

    for (int i = 0; i < T; i++)
    {
        init();
        input();
        solve();
        print();
    }

    return 0;
}