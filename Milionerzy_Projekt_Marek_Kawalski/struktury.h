/** @file */
#	ifndef struktury_h
#	define struktury_h
/**This macro removes secure warnings.*/
#	define _CRT_SECURE_NO_WARNINGS
#	include <stdio.h>
#	include <stdlib.h>
/**Enumeration which defines bool type. Bool has proved to be very useful while checking if the questions
have appeared.*/
typedef enum { TRUE = 1, FALSE = 0 } bool;
/**This struct is used so as to have an access to data connected with questions, namely
the questions themselves, a,b,c or d variants of plausible answers and finally correct answers.
It also contains information if the question has already been used. I used typedef so as not to
use a key word "struct" prior to each pHead pointer. It also contains a pointer to the next question.*/
typedef struct question
{
	char question [100], answer_A [100], answer_B[100], answer_C[100], answer_D[100], correct_answer[10];
	int number_of_question;
	bool has_it_appeared;
	struct question* pNext;
}quest;

/**This struct is created in order to store players names, information about their incomes during game 
and a pointer to the next player.*/
typedef struct leaderboard
{
	char name[50];
	char how_much_money[50];
	struct leaderboard* pNext;

}leaderboard;

#endif