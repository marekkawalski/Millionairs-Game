#   include <stdlib.h>
#	include <crtdbg.h>
#   include <stdio.h>
#	include "funkcje.h"
#	include "struktury.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(NULL));
	quest* pHead;
	pHead = NULL;
	leaderboard* Head;
	Head = NULL;
	read_from_file(&pHead, "Text.txt");
	display_name();
	game_manu(&pHead, &Head, "Ranking.txt");
	delete_list(&pHead);
	delete_list_of_players(&Head);

	return 0;
}