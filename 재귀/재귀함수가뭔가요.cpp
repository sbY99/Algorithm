#include <iostream>
#include <string>
using namespace std;

int N;
string s1, s2, s3_1, s3_2, s3_3, s4, s5;

void init();
void input();
void rec(int n);

void init()
{
    s1 = "____";
    s2 = "\"재귀함수가 뭔가요?\"\n";
    s3_1 = "\"잘 들어보게. 옛날옛날 한 산 꼭대기에 이세상 모든 지식을 통달한 선인이 있었어.\n";
    s3_2 = "마을 사람들은 모두 그 선인에게 수많은 질문을 했고, 모두 지혜롭게 대답해 주었지.\n";
    s3_3 = "그의 답은 대부분 옳았다고 하네. 그런데 어느 날, 그 선인에게 한 선비가 찾아와서 물었어.\"\n";
    s4 = "\"재귀함수는 자기 자신을 호출하는 함수라네\"\n";
    s5 = "라고 답변하였지.\n";
}

void input()
{
    cin >> N;
}

void rec(int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << s1;
    }
    cout << s2;

    if (n == N)
    {
        for (int i = N; i > 0; i--)
        {
            cout << s1;
        }
        cout << s4;
        for (int i = N; i >= 0; i--)
        {

            for (int j = i; j > 0; j--)
            {
                cout << s1;
            }
            cout << s5;
        }
        return;
    }

    for (int i = 0; i < n; i++)
    {
        cout << s1;
    }
    cout << s3_1;

    for (int i = 0; i < n; i++)
    {
        cout << s1;
    }
    cout << s3_2;

    for (int i = 0; i < n; i++)
    {
        cout << s1;
    }
    cout << s3_3;

    rec(n + 1);
}

int main()
{
    init();
    input();

    cout << "어느 한 컴퓨터공학과 학생이 유명한 교수님을 찾아가 물었다.\n";
    rec(0);

    return 0;
}