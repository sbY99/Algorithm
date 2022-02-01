#include <iostream>
#include <string>
#include <cstring>

using namespace std;

string List[51][20001];
string sorted[20000];
int Num[51];

void merge(string *data, int start, int mid, int end);
void merge_sort(string *data, int start, int end);
void print();

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int test_case;
    int T, N, Len;
    string name;
    cin >> T;
    for (test_case = 1; test_case <= T; ++test_case)
    {
        memset(Num, 0, sizeof(Num));
        scanf("%d", &N);
        getchar();

        //이름의 길이에 따라
        //string 배열에 저장
        for (int i = 0; i < N; i++)
        {
            cin >> name;
            Len = name.size();
            //길이에 맞게 index 1부터 들어감
            //Num 배열에는 각 길이에 따른 개수가 들어있음
            List[Len][++Num[Len]] = name;
        }
        printf("#%d\n", test_case);
        print();
    }
    return 0;
}

void print()
{
    //문자들의 길이는 1~50이므로
    for (int i = 1; i <= 50; i++)
    {
        //단어 0개면 넘어감
        if (Num[i] == 0)
        {
            continue;
        }
        //단어 1개면 출력 후 넘어감
        else if (Num[i] == 1)
        {
            cout << List[i][1] << endl;
            continue;
        }
        //1개 이상이면 merge sort실행
        //List에는 인덱스가 1부터 들어가므로
        merge_sort(List[i], 1, Num[i]);
        for (int j = 1; j <= Num[i]; j++)
        {
            if (List[i][j] != List[i][j - 1])
            {
                cout << List[i][j] << endl;
            }
        }
    }
}

void merge(string *data, int start, int mid, int end)
{
    int i = start;
    int j = mid + 1;
    int k = start;

    while (i <= mid && j <= end)
    {
        if (data[i] <= data[j])
        {
            sorted[k] = data[i];
            i++;
        }
        else
        {
            sorted[k] = data[j];
            j++;
        }
        k++;
    }
    if (i > mid)
    {
        for (int t = j; t <= end; t++)
        {
            sorted[k] = data[t];
            k++;
        }
    }
    else
    {
        for (int t = i; t <= mid; t++)
        {
            sorted[k] = data[t];
            k++;
        }
    }

    for (int t = start; t <= end; t++)
    {
        data[t] = sorted[t];
    }
}
void merge_sort(string *data, int start, int end)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        merge_sort(data, start, mid);
        merge_sort(data, mid + 1, end);
        merge(data, start, mid, end);
    }
}
