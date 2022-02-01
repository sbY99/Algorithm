#include <iostream>
using namespace std;

int arr[8];

int main(int argc, char **argv)
{
    for (int i = 0; i < 8; i++)
    {
        scanf("%d", &arr[i]);
    }
    int asc_count = 0;
    int dec_count = 0;
    for (int i = 0; i < 7; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            dec_count++;
        }
        else
        {
            asc_count++;
        }
    }

    if (dec_count == 7)
    {
        printf("descending");
    }
    else if (asc_count == 7)
    {
        printf("ascending");
    }
    else
    {
        printf("mixed");
    }
    return 0;
}
