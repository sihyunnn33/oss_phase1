#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
	int com[3] = { 0, 0, 0 };
	int user[3] = { 0, 0, 0 };
	int challenge = 1;
	int strike = 0, ball = 0;

	srand((int)time(NULL));

	for (int i = 0; i < 3; i++)
	{
		com[i] = rand() % 10;
		if (com[i] == com[i - 1])
			i--;
	}

	printf("Start Game! \n");

	while (1)
	{
		strike = 0;
		ball = 0;

		printf("enter 3 numbers(0~9) :");
		scanf("%d %d %d", &user[0], &user[1], &user[2]);

		for (int i = 0; i < 3; i++)
		{
			if (com[i] == user[i])
				strike++;
			else if (com[i] == user[i - 1] || com[i] == user[i + 1] || com[i] == user[i + 2])
				ball++;
		}
		printf("%dth challenge result : %d strike, %d ball !! \n", challenge, strike, ball);

		challenge++;

		if (strike == 3)
		{
			printf("Game Over !");
			break;
		}

	}

	return 0;
}