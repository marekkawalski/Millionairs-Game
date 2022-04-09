#define _CRT_SECURE_NO_WARNINGS
#   include <stdio.h>
#   include <stdlib.h>
#	include "struktury.h"
#	include "funkcje.h"
#   include <string.h>
#   include <time.h>

void read_from_file(quest**pHead, char *name_of_file )
{
	FILE* textfile=fopen(name_of_file, "r");
	if (!textfile)
	{
		printf("We are having trouble reading your textfile. Try again later.\n");
		exit(0);
	}
	else
	{
	char question[MAX], answer_A[MAX], answer_B[MAX], answer_C[MAX], answer_D[MAX], correct_answer[10];
		while (fgets(question, MAX, textfile)&&fgets(answer_A, MAX, textfile)&&fgets(answer_B, MAX, textfile)
			&&fgets(answer_C, MAX, textfile)&&fgets(answer_D, MAX, textfile)&&fgets(correct_answer, 10, textfile))
		{
			create_a_single_linked_list_by_pushing_back(pHead, question, answer_A, answer_B, answer_C, answer_D, correct_answer);
		}
		fclose(textfile);
	}
}
void create_a_single_linked_list_by_pushing_back(quest** pHead, char question [MAX], char answer_A [MAX], char answer_B [MAX], char answer_C [MAX], char answer_D [MAX], char correct_answer[10])
{
	if ((*pHead)==NULL)
	{
		*pHead = (quest*)malloc(sizeof(quest));
		strcpy((*pHead)->question, question);
		strcpy((*pHead)->answer_A, answer_A);
		strcpy((*pHead)->answer_B, answer_B);
		strcpy((*pHead)->answer_C, answer_C);
		strcpy((*pHead)->answer_D, answer_D);
		strcpy((*pHead)->correct_answer,correct_answer);
		(*pHead)->number_of_question = 0;
		(*pHead)->has_it_appeared = FALSE;
		(*pHead)->pNext = NULL;		
	}
	else
	{
		quest* p = *pHead;
		int counter = 1;
		while (p->pNext)
		{
			p = p->pNext;
			counter++;
		}
		p->pNext= (quest*)malloc(sizeof(quest));
		strcpy(p->pNext->question, question);
		strcpy(p->pNext->answer_A, answer_A);
		strcpy(p->pNext->answer_B, answer_B);
		strcpy(p->pNext->answer_C, answer_C);
		strcpy(p->pNext->answer_D, answer_D);
		strcpy(p->pNext->correct_answer,correct_answer);
		p->pNext->number_of_question=counter;
		p->pNext->has_it_appeared = FALSE;
		p->pNext->pNext = NULL;
	}
}
void print_list(quest* pHead)
{
	if (pHead)
	{
		quest* p = pHead;
		while (p)
		{
			printf("Question number: %d %s%s%s%s%s%s\n", p->number_of_question, p->question, p->answer_A, p->answer_B, p->answer_C, p->answer_D, p->correct_answer);
			p = p->pNext;
		}
	}
	else
		printf("No list has been detected.\n");
}
void delete_list(quest** pHead)
{
	quest* p = NULL;
	if ((*pHead))
	{
		p = (*pHead)->pNext;
		free(*pHead);
		*pHead = p;
		delete_list(pHead);
	}
}
quest* search_question(quest* pHead, int question_number)
{
	if (pHead)
	{
		quest* p = pHead;
 		while (p && (p->number_of_question != question_number))
		{
			p = p->pNext;
		}
		return p;
	}
}
int amount_of_questions(quest* pHead)
{
	if(pHead) return 1 + amount_of_questions(pHead->pNext);
	else return 0;
}
void give_us_random_question(quest**pHead, leaderboard**Head, char** filename)
{
	if (*pHead)
	{
		int i = 0;
		int k = amount_of_questions(*pHead);
		char y[10];
		char z[] = "y";
		char w[10];
		char money[50];
		bool was_ask_the_audience = FALSE;
		bool was_call_a_friend = FALSE;
		bool was_50_50 = FALSE;
		quest* p;
		time_t start;
		time_t end;
		int solution;
		double diffrence;
		int t = 1;
		if (k < 12)
		{
			printf("The amount of questions turned out to be insufficient to start a game.\n");
			return 0;
		}
		char name[50];
		printf("What's your name?\n");
		scanf("%s", name);
		printf("\n");
		time(&start);
		while (i<k && i<12) 
		{
			int w = generate_random_number(k);
			p = search_question(*pHead, w);
 			if ((p->has_it_appeared) == FALSE)
			{
			L:
				what_question(t);
				wait(2);
				printf("\n%sA)%sB)%sC)%sD)%s\n", p->question, p->answer_A, p->answer_B, p->answer_C, p->answer_D);
			K:
				scanf("%s", y);
				if (y[0]==p->correct_answer[0] || y[0]==p->correct_answer[0]-32)
				{
					how_much_money(t);
					t++;
					if (i == 11)
					{
						strcpy(money, "1.000.000");
					}
				}
				else if (y[0] == 64 && was_ask_the_audience==FALSE)
				{
					printf("You have choosen Ask audience lifeline\n");
					was_ask_the_audience = TRUE;
					ask_the_audience(*pHead, p->number_of_question);
					printf("Type your answer\n");
					goto K;
				}
				else if (y[0] == 35 && was_call_a_friend==FALSE)
				{
					printf("You have choosen call a friend lifeline\n");
					was_call_a_friend = TRUE;
					call_a_friend(*pHead, name, p->number_of_question);
					printf("Type your answer\n");
					goto K;
				}
				else if (y[0] == 36 && was_50_50==FALSE)
				{
					printf("You have choosen 50/50 lifeline\n");
					was_50_50 = TRUE;
					fifty_fifty(*pHead, p->number_of_question);
					printf("Type your answer\n");
					goto K;
				}
				else if (y[0] == 64 && was_ask_the_audience == TRUE)
				{
					printf("You have already used ask_the_audience lifeline. Try to guess.\n\n");
					wait(2);
					goto L;
				}
				else if (y[0] == 35 && was_call_a_friend == TRUE)
				{
					printf("You have already used call_a_friend lifeline. Make a choice\n\n");
					wait(2);
					goto L;
				}
				else if (y[0] == 36 && was_50_50 == TRUE)
				{
					printf("You have already used 50/50 lifeline.\n");
					wait(2);
					goto L;
				}
				else if ((y[0] !=p->correct_answer[0])&& (y[0] == 'a' || y[0] == 'b' || y[0] == 'c' || y[0] == 'd' || y[0] == 'A' || y[0] == 'B' || y[0] == 'C' || y[0] == 'D'))
				{
					printf("You have given an incorrect answer!\n");
					printf("Correct answer was  %s\n", p->correct_answer);
					if (t>2 && t<7 )
					{
						printf("You have won the guaranteed amount of money!\nYou get 1,000$\n\n");
						strcpy(money, "1.000$");
					}
					else if (t >= 7)
					{
						printf("You have won the guaranteed amount of money!\nYou get 50,000$\n\n");
						strcpy(money, "50.000$");
					}
					else if (t == 1 || t==2)
					{
						printf("Unfortunately you get 0,00$\n\n");
						strcpy(money, "0.00$");
					}
					i = 12;
				}
				else if (y[0]=='*')
				{
					printf("Correct answer was  %s\n", p->correct_answer);
					printf("Type your answer\n");
					goto K;
				}
				else
				{
					printf("Symbol has not been recognized!\nChoose once again\n");
					goto K;
				}
				p->has_it_appeared = TRUE;
				i++;
			}
		} 
		time(&end);
		int m=1;
		int s = 1;
		diffrence = difftime(end, start);
		m = (int)diffrence / 60;
		s = diffrence - (m * 60);
		write_to_file(Head, filename, name, money, m,s);
		printf("Do you want to play again? (y/n)\n");
		scanf("%s", w);
		if(!strncmp(w, z, 1))
		{
			printf("\n\n\n\t\t\t\t\t\t\t\t\t\tPress Enter...");
			getchar();
			system("cls");
			sub_menu(pHead, Head,filename);
		}
		else
		{
			printf("Thanks for your mesmerizing game.\n");
			return 0;
		}
	}
	else printf("Error loading the list");
}
int generate_random_number(int number)
{
	int liczba;
	liczba = rand() % number;
	return liczba;
}
void how_much_money(int k)
{
	switch (k)
	{
	case 1: printf("Congratulations you win \t500$\n\n\n");
		break;
	case 2: printf("Congratulations you win \t1.000$\n\n\n");
		break;
	case 3: printf("Congratulations you win \t2.000$\n\n\n");
		break;
	case 4: printf("Congratulations you win \t5.000$\n\n\n");
		break;
	case 5: printf("Congratulations you win \t10.000$\n\n\n");
		break;
	case 6: printf("Congratulations you win \t20.000$\n\n\n");
		break;
	case 7: printf("Congratulations you win \t50.000$\n\n\n");
		break;
	case 8: printf("Congratulations you win \t75.000$\n\n\n");
		break;
	case 9: printf("Congratulations you win \t150.000$\n\n\n");
		break;
	case 10: printf("Congratulations you win \t250.000$\n\n\n");
		break;
	case 11: printf("Congratulations you win \t500.000$\n\n\n");
		break;
	case 12: printf("Congratulations you win \t1.000.000$\n\n\n");
		break;
	default: printf("A flow has appeared with displaying how much money the player will get\n\n\n");
		break;
	}
}
void what_question(int k)
{
	switch (k)
	{
	case 1: printf("\nYou are answering a question for  500$\nRemember that you have three lifelines\nTo ask the audience type '@'\nTo call a friend type '#'\nTo choose 50/50 type '$'\n");
		break;
	case 2: printf("\nThis question is worth  1.000$  and this amount is guaranteed\n");
		break;
	case 3: printf("\nThis time you can win as much as  2.000$\n");
		break;
	case 4: printf("\nDon't lose your head and take  5.000$\n");
		break;
	case 5: printf("\nHit the nail on the head and grab  10.000$\n");
		break;
	case 6: printf("\nMoving onto  20.000$\n\n");
		break;
	case 7: printf("\nYou can become a Porsche owner now. It's a question for  50,000$  and this amount is guaranteed\n");
		break;
	case 8: printf("\nWin  75.000$\n\n");
		break;
	case 9: printf("\nFour questions to go. Question for  150.000$\n");
		break;
	case 10: printf("\nAlmost there. Get  250.000$\n");
		break;
	case 11: printf("\nYou are halfway to becoming a billionaire!  500.000$\n");
		break;
	case 12: printf("\nFinal question! Don't mess it up  1.000.000$\n");
		break;
	default: printf("\nA flow has appeared with displaying how much money the player will get\n");
		break;
	}
}
void display_name()
{
	printf("\t\t\t\tWHO WANTS TO BE A...\n\n\n");
	
	printf("\t  $$$  $$$    $$  $$     $$     $$      $$   $$     $      $$  $$$$   $$$$\n");
	printf("\t $$$ $$ $$$   $$  $$     $$   $$  $$   $$ $$$    $$ $ $$   $$  $ $$   $$\n");
	printf("\t$$$      $$$  $$  $$$$$  $$     $$    $$$       $$     $$  $$  $  $$  $$$$\n\n\n\n");

}
void sub_menu(quest**pHead, leaderboard** Head, char** filename)
{
	int k=4;
	printf("Now choose one of the following options:\n\n\n");
	printf("*****Start game\n");
	printf("*****How to play\n");
	printf("*****About the original game\n");
	printf("*****Exit game\n\n");
	printf("Type 1,2,3 or 4 and hit enter\n");
	scanf("%d", &k);
	printf("\n\n\n\t\t\t\t\t\t\t\t\t\tPress Enter...");
	getchar();
	system("cls");
	switch (k)
	{
	case 1:	check_guard(pHead);
			give_us_random_question(pHead, Head, filename);
			break;
	case 2:	how_to_play();
			printf("\n\n\n\t\t\t\t\t\t\t\t\t\tPress Enter...");
			getchar();
			system("cls");
			sub_menu(pHead, Head, filename);
			break;
	case 3:	about();
			printf("\n\n\n\t\t\t\t\t\t\t\t\t\tPress Enter...");
			getchar();
			system("cls");
			sub_menu(pHead, Head, filename);
			break;
	case 4:	
			return 0;
			break;
	default:
			printf("Please choose once again.\n");
			sub_menu(pHead, Head, filename);
			break;
	}
}
void how_to_play()
{
	printf("The game is open to anyone willing to put their knowledge to the test in a series of questions and answers.Just keep your wits about you, have fun, and get rich!So if you’re in the mood to make a quick million dollars for yourself, this is your chance.\n");
	printf("The game consists of 12 questions. Once a question is provided player must answer simply by typing a,b,c or d. If you don't happen to know the answer ask for help by typing @ or # or $. In this case you will be provided with a lifeline. If the answer is correct you shall continue playing with the amount of money increased. Otherwise you lose and take guaranteed amount of money or you just lose.");
	printf("The player is given three lifelines:\n50/50: the game's computer eliminates two wrong answers from the current question, leaving behind the correct answer and one incorrect answer\nPhone a friend: the contestant calls a virtual friend who tends to always indicate the right answer\nAsk the audience: The audience takes voting pads attached to their seats and votes for the answer that they believe is correct\n");
}
void about()
{
printf("Who Wants to Be a Millionaire? debuted in Britain on 4 September 1998, with episodes broadcast on the ITV network.When it began airing,\n the show was hosted by Chris Tarrant, and became an instant hit – at its peak in 1999, one edition of the show was watched by over 19 million viewers.\n While most of the contestants were predominantly members of the general public who had applied to take part, the show later featured special celebrity editions during its later years, often coinciding with holidaysand special events.");
printf("\nOn 22 October 2013, Tarrant decided to leave the programme after hosting it for 15 years.His decision subsequently led ITV to make plans to cancel the programme at the end of his contract, with no further specials being made other than those that were already planned.\n Tarrant's final episode was a special clip show entitled 'Chris' Final Answer', which aired on 11 February 2014.\n");
printf("Four years later, ITV revived the programme for a special 7 - episode series, to commemorate the 20th anniversary of the British original.\n This series of special episodes was hosted by Jeremy Clarkson and aired every evening between 5 and 11 May 2018.\n The revival received mostly positive reviews from critics and fans, and, as well as high viewing figures, led to ITV renewing the show for another series with Clarkson returning as host.\n");
}
void game_manu(quest** pHead, leaderboard** Head, char** filename)
{
	wait(2);
	printf("\t .............Welcome to the world of possibilities and affluent people.............\n");
	printf("\n\n\t......Prepare for an unforgettable adventure......");
	wait(2);
	printf("\n\n\t......You are now gonna experience learning whilst having a whale of time......");
	wait(2);
	printf("\n\n\n\n\n\n\t Game made by   BIKE_STUDIOS_INC   worlds leading game developement company\n");
	printf("\t\t\t\t\t\t\t\t\t\tPress Enter...");
	getchar();
	system("cls");
	printf("\t\tPRIVACY POLICY and TERMS of USE\n\n");
	printf("We may use the personal information we obtain to:\n");
	printf("provide and enhance our Services, such as registering you or your device for a Service, identifyingand authenticating you so you may useand interact with third - party services, and improvingand customizing your experience within the Services");
	printf("\ncommunicate with you;\n");
	printf("provide customer support;\n");
	printf("operate, evaluateand improve our business, including developing new productsand services, managing our communications, analyzing our Servicesand customer base, conducting market research, aggregatingand anonymizing data, performing data analytics, and undertaking accounting, auditingand other internal functions;\n");
	printf("protect against, identifyand prevent fraudand other criminal activity, claimsand other liabilities;and\n");
	printf("comply withand enforce applicable legal requirements, relevant industry standardsand our policies, including this Privacy Policyand the applicable Terms of Use for a Service.\n");
	printf("We may combine information we obtain about you for the purposes described above.We also may use theinformation we obtain in other ways for which we provide specific notice at the time of collection or otherwise with your consent.\n");
	printf("\t\t\t\t\t\t\t\t\t\tPress Enter...");
	getchar();
	system("cls");
	sub_menu(pHead, Head, filename);
}
void write_to_file(leaderboard** Head, char** filename, char name[50], char money[50], int minutes, int seconds )
{
	FILE* textfile = fopen(filename, "a");
	if (!textfile)
	{
		printf("We are having trouble reading your textfile. Try again later.\n");
		return 0;
	}
	else
	{
		int size;
		fseek(textfile, 0, SEEK_END);
		size = ftell(textfile);
		if (0 == size)
		{
			fprintf(textfile, "\t\t\tLeaderboard\n");
		}
		create_list_of_players_by_pushing_front(Head, name, money);
		fprintf(textfile, "Player's name: %s\nYou have: %s\nYour game took %d minutes %d seconds\n\n", (*Head)->name, (*Head)->how_much_money, minutes,seconds);
		fclose(textfile);
	}
}
void create_list_of_players_by_pushing_front(leaderboard** pHead, char name[50], char money[50])
{
	leaderboard* p = (leaderboard*)malloc(sizeof(leaderboard));
	strcpy(p->name, name);
	strcpy(p->how_much_money, money);
	p->pNext = (*pHead);
	*pHead = p;
}
void wait(int seconds)
{
	clock_t end_of_waiting;
	end_of_waiting = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < end_of_waiting) {}
}
void call_a_friend(quest* pHead, char name[50], int number_of_question)
{
	int j = generate_random_number(5);
	if (pHead)
	{
		switch (j)
		{
		case 0: printf("\nHi %s. Thanks for calling. Reffering to the question, I strongly believe that the answer is  %s\n", name, search_question(pHead, number_of_question)->correct_answer);
			break;
		case 1: printf("\nHey %s. I may not be an expert but I suppose that the answer is  %s\n", name, search_question(pHead, number_of_question)->correct_answer);
			break;
		case 2: printf("\nBonjour %s. Long time no see. In my opinion you should go for  %s\n", name, search_question(pHead, number_of_question)->correct_answer);
			break;
		case 3: printf("\nBuenos Dias %s. My dear friend, it's a long shot but I would bet  %s\n", name, search_question(pHead, number_of_question)->correct_answer);
			break;
		case 4: printf("\nDzien Dobry %s. I am positive that answer is  %s\n", name, search_question(pHead, number_of_question)->correct_answer);
			break;
		default: printf("\nError with call_a_friend_switch\n");
			break;
		}
	}
}
void fifty_fifty(quest* pHead, int number_of_question)
{
	int j = generate_random_number(4);
	quest* p = search_question(pHead, number_of_question);
	if (pHead)
	{
		switch (j)
		{
		case 0:
			if(p->correct_answer[0]=='c')
			  {
				printf("50/50 has reduced answers to:\n\t%s\tb\n", p->correct_answer);
			  }
			else
			{
				printf("50/50 has reduced answers to:\n\t%s\tc\n", p->correct_answer);
			}
			break;
		case 1: 
			if (p->correct_answer[0] == 'a')
			{
				printf("50/50 has reduced answers to:\n\t%s\td\n", p->correct_answer);
			}
			else
			{
				printf("50/50 has reduced answers to:\n\tb\n\t%s", p->correct_answer);
			}
			break;
		case 2:
			if (p->correct_answer[0] == 'b')
			{
				printf("50/50 has reduced answers to:\n\tc\n\t%s", p->correct_answer);
			}
			else
			{
				printf("50/50 has reduced answers to:\n\tb\n\t%s", p->correct_answer);
			}
			break;
		case 3:
			if (p->correct_answer[0] == 'd')
			{
				printf("50/50 has reduced answers to:\n\ta\n\t%s\n", p->correct_answer);
			}
			else
			{
				printf("50/50 has reduced answers to:\n\td\n\t%s\n", p->correct_answer);
			}
			break;
		default: printf("\nError with fifty_fifty switch\n");
			break;
		}
	}
}
void ask_the_audience(quest* pHead, int number_of_question)
{
	if (pHead)
	{
		quest* p = search_question(pHead, number_of_question);
		int k = generate_random_number(21);
		int t = generate_random_number(16);
		int w = generate_random_number(31);
		int r = 100 - k - t - w;
		
		if (p->correct_answer[0] == 'a')
		{
			printf("The answers are as follows:\n");
			printf("%d%% of audience thinks that correct answer is: ", r);
			wait(1);
			printf("%s", p->correct_answer);
			printf("%d%% of audience thinks that correct answer is: ",k);
			wait(1);
			printf("b\n");
			printf("%d%% of audience thinks that correct answer is: ",t);
			wait(1);
			printf("c\n");
			printf("%d%% of audience thinks that correct answer is: ",w);
			wait(1);
			printf("d\n");

		}
		else if (p->correct_answer[0] == 'b')
		{
			printf("The answers are as follows:\n");
			printf("%d%% of audience thinks that correct answer is: ", k);
			wait(1);
			printf("a\n");
			printf("%d%% of audience thinks that correct answer is: ", r);
			wait(1);
			printf("%s",p->correct_answer);
			printf("%d%% of audience thinks that correct answer is: ", t);
			wait(1);
			printf("c\n");
			printf("%d%% of audience thinks that correct answer is: ", w);
			wait(1);
			printf("d\n");
		}
		else if (p->correct_answer[0] == 'c')
		{
			printf("The answers are as follows:\n");
			printf("%d%% of audience thinks that correct answer is: ", k);
			wait(1);
			printf("a\n");
			printf("%d%% of audience thinks that correct answer is: ", w);
			wait(1);
			printf("b\n");
			printf("%d%% of audience thinks that correct answer is: ", r);
			wait(1);
			printf("%s", p->correct_answer);
			printf("%d%% of audience thinks that correct answer is: ", t);
			wait(1);
			printf("d\n");
		}
		else if (p->correct_answer[0] == 'd')
		{
			printf("The answers are as follows:\n");
			printf("%d%% of audience thinks that correct answer is: ", k);
			wait(1);
			printf("a\n");
			printf("%d%% of audience thinks that correct answer is: ", w);
			wait(1);
			printf("b\n");
			printf("%d%% of audience thinks that correct answer is: ", t);
			wait(1);
			printf("c\n");
			printf("%d%% of audience thinks that correct answer is: ", r);
			wait(1);
			printf("%s", p->correct_answer);
		}
	}
}
void delete_list_of_players(leaderboard** pHead)
{
	quest* p = NULL;
	if ((*pHead))
	{
		p = (*pHead)->pNext;
		free(*pHead);
		*pHead = p;
		delete_list_of_players(pHead);
	}
}
void print_list_of_players(leaderboard* pHead)
{
	if (pHead)
	{
		leaderboard* p = pHead;
		while (p)
		{
			printf("Name: %s\nMoney: %s\n",p->name, p->how_much_money);
			p = p->pNext;
		}
	}
	else
		printf("No list_of_players has been detected.\n");
}
void check_guard(quest** pHead)
{
	if (*pHead)
	{
		quest* p = *pHead;
		int counter = 0;
		while (p)
		{
			if (p->has_it_appeared == FALSE) counter++;
			p = p->pNext;
		}
		p = *pHead;
		if (counter < 12)
		{
			while (p)
			{
				p->has_it_appeared = FALSE;
				p = p->pNext;
			}
		}
	}
}