/* 
* @Author: Adrien Chardon
* @Date:   2014-02-14 09:58:41
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-22 22:26:47
*/

/*
	highest : 336
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h> /* time() */
#include <unistd.h> /* usleep() */

#include "constantes.h"
#include "AsyncInput.h"
#include "print.h"
#include "play.h"
#include "init.h"
#include "score.h"

void ft_menu_main(void);
void ft_menu_commands(t_keymap *keymap);

int main(void)
{
	set_conio_terminal_mode(); /* auto cleanup enabled */
	srand(time(NULL));

	ft_menu_main();

	return 0;
}

/*============================================================================*/

void ft_menu_main(void)
{
	int quit = 0;
	int choice, actual = 0;
	char strNone[] = "  ", strArrowR[] = "=>", strArrowL[] = "<=";
	t_keymap keymap;

	/* init keyboard conf. and show it */
	ft_init_keymap(&keymap);
	ft_menu_commands(&keymap);

	do {
		/* clear screen + print help + menu */
		clear_screen();
		printf(	"+---------------+\n"
				"|     MENU      |\n"
				"+---------------+\n"
				"|%s   Jouer   %s|\n"
				"|%s Commandes %s|\n"
				"|%s  Scores   %s|\n"
				"|%s  Quitter  %s|\n"
				"+---------------+\n",
				actual == 0 ? strArrowR : strNone, actual == 0 ? strArrowL : strNone,
				actual == 1 ? strArrowR : strNone, actual == 1 ? strArrowL : strNone,
				actual == 2 ? strArrowR : strNone, actual == 2 ? strArrowL : strNone,
				actual == 3 ? strArrowR : strNone, actual == 3 ? strArrowL : strNone);

		/* wait for a key press while being nice with the cpu */
		while (!kbhit())
			usleep(1000*1000/FPS);
		choice = getchar();

		/* note : cant use a switch because of non constant expression */
		/* direct choice */
		if (choice == keymap.up)
			actual--;
		if (choice == keymap.down)
			actual++;		
		actual = (actual+4)%4;
		if (choice == keymap.quit)
			quit = 1;

		/* enter, need to know which choice was selected */
		if (choice == keymap.enter)
		{
			if (actual == 0)
				ft_play(&keymap);
			if (actual == 1)
				ft_menu_commands(&keymap);
			if (actual == 2)
				ft_print_scores();
			if (actual == 3)
				quit = 1;
		}
	} while (!quit);
}

void ft_menu_commands(t_keymap *keymap)
{
	clear_screen();
	
	printf(	"+---------------------+\n"
			"|      COMMANDES      |\n"
			"+---------------------+\n"
			"\n"
			" %c : valider / tirer\n"
			" %c : quitter\n"
			"\n"
			" Deplacements :\n"
			" %c : haut\n"
			" %c : bas\n"
			" %c : gauche\n"
			" %c : droite\n"
			"\n"
			"Appuyer sur une touche pour continuer.\n",
			keymap->enter, keymap->quit,
			keymap->up, keymap->down, keymap->left, keymap->right);

	getchar();
}

