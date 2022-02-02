///////////////////////////////
#include <stdio.h>
int main(void)
{
	int test_case;
	int T;
	setbuf(stdout, NULL);
	scanf("%d", &T);
	int N, M, check;
	for (test_case = 1; test_case <= T; ++test_case)
	{
		scanf("%d %d", &N, &M);
		check = 0;
		if (M == 0)
		{
			printf("#%d OFF\n", test_case);
			continue;
		}
		//N을 줄여가며 M의 하위 비트가 1로 켜져있는지 검사
		while (N != 0)
		{
			if (M % 2 == 0)
			{
				check++;
				break;
			}
			M >>= 1;
			N--;
		}
		//check가 0이면 On, 아니면 Off.
		if (check == 0)
		{
			printf("#%d ON\n", test_case);
		}
		else
		{
			printf("#%d OFF\n", test_case);
		}
	}
	return 0; //정상종료시 반드시 0을 리턴해야 합니다.
}