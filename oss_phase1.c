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

	return 0;
}