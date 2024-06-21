#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define BASE_NUM 4


void generate_com_numbers(int *numbers) { //컴퓨터의 랜덤 숫자, 중복 없이.
    int used[10] = {0};
    int count = 0;
    while (count < 4){
        int num = rand() % 10;
        if (!used[num]){
            numbers[count++] = num;
            used[num] = 1;
        }
    }
}

void get_user_num(int *numbers){ //유저 직접 입력 중복 없이
    printf("Enter your secret numbers (4 different digits *ex: 4 3 1 9) : ");
    for (int i = 0; i < 4; i++) {
        scanf("%d", &numbers[i]);
    }
}

void get_guess(int *guess) { //유저 추측
    printf("Enter your guess (4 different digits): ");
	
    for (int i = 0; i < 4; i++) {
        scanf("%d", &guess[i]);
    }
	printf("\n");
}

void generate_all_possible_numbers(int possible_numbers[][4], int *count) { //가능한 모든 조합의 숫자를 넣어둔 2차원 배열
    *count = 0;
    for (int i = 0; i < 10000; i++) {
        int a = i / 1000;
        int b = (i / 100) % 10;
        int c = (i / 10) % 10;
        int d = i % 10;
        if (a != b && a != c && a != d && b != c && b != d && c != d) {
            possible_numbers[*count][0] = a;
            possible_numbers[*count][1] = b;
            possible_numbers[*count][2] = c;
            possible_numbers[*count][3] = d;
            (*count)++;
        }
    }
	
}

void get_feedback(int *guess, int *numbers, int *strike, int *ball, int *out) {
    *strike = 0;
    *ball = 0;
    *out = 0;
    for (int i = 0; i < 4; i++) {
        if (guess[i] == numbers[i]) {
            (*strike)++;
        } else {
            int found = 0;
            for (int j = 0; j < 4; j++) {
                if (guess[i] == numbers[j]) {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                (*out)++;
            } else {
                (*ball)++;
            }
        }
    }
}

void print_feedback(int *guess, int strike, int ball, int out) {
    if (strike == 0 && ball == 0) {
        printf("Guess: %d %d %d %d : OUT\n", guess[0], guess[1], guess[2], guess[3]);
    } else {
        printf("Guess: %d %d %d %d : %d Strike, %d Ball\n",
               guess[0], guess[1], guess[2], guess[3], strike, ball);
    }
}

void filter_possible_numbers(int possible_numbers[][4], int *count, int *guess, int strike, int ball, int out) {
    int new_count = 0;
    for (int i = 0; i < *count; i++) {
        int current_strike = 0, current_ball = 0, current_out = 0;
        for (int j = 0; j < 4; j++) {
            if (possible_numbers[i][j] == guess[j]) {
                current_strike++;
            } else {
                int found = 0;
                for (int k = 0; k < 4; k++) {
                    if (possible_numbers[i][j] == guess[k]) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    current_out++;
                } else {
                    current_ball++;
                }
            }
        }
        if (current_strike == strike && current_ball == ball && current_out == out) {
            for (int j = 0; j < 4; j++) {
                possible_numbers[new_count][j] = possible_numbers[i][j];
            }
            new_count++;
        }
    }
    *count = new_count;
}

int main(void) {
    srand(time(0));

    int user_num[4];
    get_user_num(user_num);

    int computer_numbers[4];
    generate_com_numbers(computer_numbers);

    int possible_numbers[5040][4]; // 최대 가능한 5040개의 조합 (중복없는 4자리 수)
    int possible_count;
    generate_all_possible_numbers(possible_numbers, &possible_count);

    int user_attempts = 0, computer_attempts = 0;
    int user_strike = 0, user_ball = 0, user_out = 0;
    int computer_strike = 0, computer_ball = 0, computer_out = 0;


	printf("\n----------Start Game!!!------------\n");

    while (user_strike < 4 && computer_strike < 4) {
        // User's turn
        int user_guess[4]; // 유저 추측
        get_guess(user_guess);
        get_feedback(user_guess, computer_numbers, &user_strike, &user_ball, &user_out);
		printf(" Your ");
        print_feedback(user_guess, user_strike, user_ball, user_out);
        user_attempts++;

        if (user_strike == 4) {
            printf("User wins! You guessed the number in %d attempts.\n", user_attempts);
			printf("Game Over !");
            break;
        }

        // Computer's turn
        int computer_guess[4]; //컴퓨터 추측
        for (int i = 0; i < 4; i++) {
            computer_guess[i] = possible_numbers[0][i];
        }
        get_feedback(computer_guess, user_num, &computer_strike, &computer_ball, &computer_out);
		printf("Com's ");
        print_feedback(computer_guess, computer_strike, computer_ball, computer_out);
        filter_possible_numbers(possible_numbers, &possible_count, computer_guess, computer_strike, computer_ball, computer_out);
        computer_attempts++;

        if (computer_strike == 4) {
            printf("\nComputer wins! Computer guessed the number in %d attempts.\n", computer_attempts);
			printf("Game Over !");
            break;
        }
    }

    if (user_strike < 4 && computer_strike < 4) {
        printf("It's a draw!\n");
    }

    sleep(5);

    return 0;
}


