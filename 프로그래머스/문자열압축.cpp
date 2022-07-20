#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cmath>

using namespace std;

int solution(string s)
{
    int answer = 1000;
    int range = s.length();

    for (int i = 1; i <= range; i++)
    {
        int part_result = 0, part_length = 0;
        int start = 0, end = i;

        string prev;

        for (int k = start; k < end; k++)
        {
            prev += s[k];
        }
        start += i;
        end = start + i;
        part_length++;

        while (end <= range)
        {
            string curr;
            for (int k = start; k < end; k++)
            {
                curr += s[k];
            }

            if (prev == curr)
                part_length++;
            else
            {
                part_result += i;

                if (part_length >= 2)
                    part_result++;
                if (part_length >= 10)
                    part_result++;
                if (part_length >= 100)
                    part_result++;
                if (part_length >= 1000)
                    part_result++;

                part_length = 1;
                prev = curr;
            }
            start += i;
            end = start + i;
        }

        part_result += i;
        if (part_length >= 2)
            part_result++;
        if (part_length >= 10)
            part_result++;
        if (part_length >= 100)
            part_result++;
        if (part_length >= 1000)
            part_result++;

        if (start < range)
        {
            part_result += (range - start);
        }
        answer = min(answer, part_result);
    }

    return answer;
}

int main()
{
    string s;
    cin >> s;
    cout << solution(s);
    return 0;
}