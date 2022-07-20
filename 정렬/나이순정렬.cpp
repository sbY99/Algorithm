#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

typedef struct _member
{
    int age;
    string name;
} Member;

int N;
Member M[100001];
Member sorted[100001];

void input();
void output();
void merge_sort(int start, int end);
void merge(int start, int mid, int end);

void input()
{
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> M[i].age >> M[i].name;
    }
}

void output()
{
    for (int i = 0; i < N; i++)
    {
        cout << M[i].age << ' ' << M[i].name << '\n';
    }
}

void merge_sort(int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        merge_sort(start, mid);
        merge_sort(mid + 1, end);
        merge(start, mid, end);
    }
}

void merge(int start, int mid, int end)
{
    int left = start;
    int right = mid + 1;
    int k = start;
    while (left <= mid && right <= end)
    {
        if (M[left].age <= M[right].age)
        {
            sorted[k++] = M[left];
            left++;
        }
        else
        {
            sorted[k++] = M[right];
            right++;
        }
    }

    if (left > mid)
    {
        for (int t = right; t <= end; t++)
        {
            sorted[k++] = M[t];
        }
    }
    else
    {
        for (int t = left; t <= mid; t++)
        {
            sorted[k++] = M[t];
        }
    }

    for (int t = start; t <= end; t++)
    {
        M[t] = sorted[t];
    }
}

int main()
{
    input();
    merge_sort(0, N - 1);
    output();
    return 0;
}