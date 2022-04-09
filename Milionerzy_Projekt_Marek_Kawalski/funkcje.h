/** @file */
#ifndef funkcje_h
#define funkcje_h
/**This macro removes secure warnings.*/
#define _CRT_SECURE_NO_WARNINGS
#   include <stdio.h>
#   include <stdlib.h>
#   include <string.h>
#	include "struktury.h"
/**This macro defines maximum value which is used in couple of functions.
@see {read_from_file}
@see {create_a_single_linked_list_by_pushing_back}
*/
#	define MAX 100
/**Function is used to read line by line data from file using gets function. All data is stored in one directional
list which is created by "create_a_single_linked_list_by_pushing_back" function".
@param pHead Pointer to a pointer to the beginning of the list
@param name_of_file name of the file where there are questions and answers
@see {create_a_single_linked_list_by_pushing_back}
@return returns nothing
*/
void read_from_file(quest** pHead, char* name_of_file);
/**Additional function which was used to check if both creating and deleting the list works properly
@param pHead pointer to the beginning of the list
@return returns nothing
*/
void print_list(quest* pHead);
/**This function is used to create a single linked list by pushing back new elements. It's used in 
collaboration with read_from_file function
@param pHead Pointer to a pointer to the beginning of the list
@param question[MAX] it's a string which size is defined at the beginning of "funkcje.h" file
@param answerA[MAX] it's a string which size is defined at the beginning of "funkcje.h" file
@param answerB[MAX] it's a string which size is defined at the beginning of "funkcje.h" file
@param answerC[MAX] it's a string which size is defined at the beginning of "funkcje.h" file
@param answerD[MAX] it's a string which size is defined at the beginning of "funkcje.h" file
@param correct_answer[10] it's a string 
@see {read_from_file}
@return returns nothing
*/
void create_a_single_linked_list_by_pushing_back(quest** pHead, char question[MAX], char answer_A[MAX], char answer_B[MAX], char answer_C[MAX], char answer_D[MAX], char correct_answer[10]);
/**This function deletes list of questions and answers so as not to have memory leaks
@param pHead Pointer to a pointer to the beginning of the list
@return returns nothing
*/
void delete_list(quest** pHead);
/**This function searches question by the number of question and returns pointer to that question. Its used in give_us_random_question function.
@param pHead pointer to the beginning of the list 
@param question_number int parameter 
@return returns pointer to to the question
*/
quest* search_question(quest* pHead,int question_number);
/**Function calculates amount of questions in the list.
@param pHead pointer to the list 
@return returns amount of questions
*/
int amount_of_questions(quest* pHead);
/**This is the foremost function in which most of other functions is executed. 
@param pHead pointer to the pointer to the beginning of the list (working on original value)
@param Head pointer to the pointer to the beginning of the second list (also original value)
@see {search_question}
@see {amount_of_questions}
@see {generate_random_number}
@see {how_much_money}
@see {what_question}
@see {call_a_friend}
@see {fifty_fifty}
@see {ask_the_audience}
@return returns nothing
*/
void give_us_random_question(quest** pHead, leaderboard**Head, char** filename);
/**Simple function which generates integer random number.
@param number it's the maximum value that can be generated
@return returns random number
*/
int generate_random_number(int number);
/**Void function which assigment is to display the amount of money the player can win.
@param k parameter which is essential to know what amount to money display with each question.
@return returns nothing
*/
void how_much_money(int k);
/**Void function which is similar to "how_much_money" function. The only diffrence is that it's displayed 
every time disregard whether the answer had been correct or not.
@param k parameter which is crucial to know what amount to money display with each question.
@return returns nothing
*/
void what_question(int k);
/**Function that using '$' characters displays "millionairs".
@param no parameters
@return returns nothing
*/
void display_name();
/**Vital function which gives the player a choice of what to do and then executes adequate functions.
@param pHead pointer to the pointer to the beginning of the list (working on original value)
@param Head pointer to the pointer to the beginning of the second list (also original value)
@param filename original file
@return returns nothing
*/
void sub_menu(quest**pHead, leaderboard** Head, char** filename);
/**Simple void function which tells the user how to play.
@param lack of parameters
@return returns nothing
*/
void how_to_play();
/**Simple void function which tells the user the story about original millionairs
@param lack of parameters
@return returns nothing
*/
void about();
/**Function which gathers various captions and couple of other functions.
@param pHead pointer to the pointer to the beginning of the list (working on original value)
@param Head pointer to the pointer to the beginning of the second list (also original value)
@param filename original file
@return returns nothing
*/
void game_manu(quest** pHead, leaderboard** Head, char** filename);
/**Function is used to open file in append mode.
@param pHead pointer to the pointer to the beginning of the second list (also original value)
@param filename original file
@param name it's the players name
@param money it's how much has the player won
@param minutes it's how long has the game lasted
@param seconds it's how long has the game lasted
@return returns nothing
*/
void write_to_file(leaderboard** pHead, char** filename, char name[50], char money[50], int minutes,int seconds);
/**Function creates list of names by pushing front. It could have been implemented in a similar way to
create_a_single_linked_list_by_pushing_back but so as to further practice my programming skills I choose 
another way.
@param Head pointer to the pointer to the beginning of the second list (also original value)
@param name it's the players name
@param money it's how much has the player won
*/
void create_list_of_players_by_pushing_front(leaderboard** pHead, char name[50], char money[50]);
/**Function reads system time and makes the programm wait by the time specified by parameter.
@param seconds how long the programm is held waiting
@return returns nothing
*/
void wait(int seconds);
/**Function is used as a call a friend lifeline.
@param pHead pointer to the beginning of the list 
@param name user's name
@param number_of_question it's current's question number
@return returns nothing
*/
void call_a_friend(quest* pHead, char name [50], int number_of_question);
/**Function is used as a fifty_fifty lifeline.
@param pHead pointer to the beginning of the list
@return returns nothing
*/
void fifty_fifty(quest* pHead, int number_of_question);
/**Function is used as a ask_the_audience lifeline.
@param pHead pointer to the beginning of the list
@param number_of_question it's current's question number
@return returns nothing
*/
void ask_the_audience(quest* pHead, int number_of_question);
/**Function deletes list of players.
@param Head pointer to the pointer to the beginning of the second list (original value)
@return returns nothing
*/
void delete_list_of_players(leaderboard** pHead);
/**A test function which prints list's of players content.
@param pHead pointer to the beginning of the list
@return returns nothing
*/
void print_list_of_players(leaderboard* pHead);
/**It's an important function which checks whether all of the questions have been used or not. If yes,
it automatically turns them all into unused questions and therefore questions can repeat after the limit
is exceeded.
@param Head pointer to the pointer to the beginning of the list (original value)
@return returns nothing
*/
void check_guard(quest** pHead);

#endif