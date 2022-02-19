#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int A, B;
long long visited[10000];
bool endCheck;
queue<int> q;

void init()
{
    memset(visited, 0, sizeof(visited));
    endCheck = false;
    while (q.size() > 0)
    {
        q.pop();
    }
}

int D(int num)
{
    return ((num * 2) % 10000);
}

int S(int num)
{
    if (num == 0)
        return 9999;
    return num - 1;
}

int L(int num)
{
    int first = num / 1000;
    int last = num % 1000;
    return (last * 10 + first);
}

int R(int num)
{
    int first = num / 10;
    int last = num % 10;
    return (last * 1000 + first);
}

void DSLR(int num)
{
    for (int i = 1; i <= 4; i++)
    {
        if (i == 1)
        {
            int next = D(num);
            if (visited[next] != 0 || next == A)
                continue;
            if (B == next)
            {
                visited[next] = visited[num] * 10 + 1;
                endCheck = true;
                return;
            }
            else
            {
                visited[next] = visited[num] * 10 + 1;
                q.push(next);
            }
        }
        else if (i == 2)
        {
            int next = S(num);
            if (visited[next] != 0 || next == A)
                continue;
            if (B == next)
            {
                visited[next] = visited[num] * 10 + 2;
                endCheck = true;
                return;
            }
            else
            {
                visited[next] = visited[num] * 10 + 2;
                q.push(next);
            }
        }
        if (i == 3)
        {
            int next = L(num);
            if (visited[next] != 0 || next == A)
                continue;
            if (B == next)
            {
                visited[next] = visited[num] * 10 + 3;
                endCheck = true;
                return;
            }
            else
            {
                visited[next] = visited[num] * 10 + 3;
                q.push(next);
            }
        }
        if (i == 4)
        {
            int next = R(num);
            if (visited[next] != 0 || next == A)
                continue;
            if (B == next)
            {
                visited[next] = visited[num] * 10 + 4;
                endCheck = true;
                return;
            }
            else
            {
                visited[next] = visited[num] * 10 + 4;
                q.push(next);
            }
        }
    }
}

void BFS()
{
    q.push(A);
    while (q.size())
    {
        int curr = q.front();
        q.pop();
        DSLR(curr);
        if (endCheck == true)
            break;
    }
}

void Output()
{
    long long temp = visited[B];
    long long result = 0;
    // reversing
    while (temp != 0)
    {
        result = result * 10 + temp % 10;
        temp /= 10;
    }
    // print
    while (result != 0)
    {
        if (result % 10 == 1)
        {
            printf("D");
        }
        else if (result % 10 == 2)
        {
            printf("S");
        }
        else if (result % 10 == 3)
        {
            printf("L");
        }
        else if (result % 10 == 4)
        {
            printf("R");
        }
        result /= 10;
    }
    printf("\n");
}

int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        init();
        cin >> A >> B;
        BFS();
        Output();
    }
}