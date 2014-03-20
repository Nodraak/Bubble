/* 
* @Author: Adrien Chardon
* @Date:   2014-02-14 13:38:57
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-22 22:13:46
*/

#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "print.h"
#include "play.h"


/* main loop to print the game board */
void ft_print_map(t_map *map)
{
	int i, j;

	/* clear screen */
	printf("\e[1;1H\e[2J");

	/* print each block of line */
	for (i = 0; i < map->size.y; ++i)
	{
		/* a separator */
		ft_print_sep_horiz(map, i);

		/* and the line */
		for (j = 0; j < PIXEL_SIZE/2; ++j)
			ft_print_line_one(map, i);
	}
}

/* print horizontal separator between lines */
void ft_print_sep_horiz(t_map *map, int currentLine)
{
	int i, j;

	for (i = 0; i < map->size.x; ++i)
	{
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);

		for (j = 0; j < PIXEL_SIZE; ++j)
		{
			/* white separator */
			if (ft_explode_bubble(map, currentLine, i, COLOR_WHITE, COUNT_AROUND_START) >= 2
				&& (i == 0 || i == SCREEN_WIDTH-1) && currentLine != 0)
				ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
			/* white separator bubbles at the edge */
			else if ((currentLine == map->pos.y || currentLine == map->pos.y + 1)
				&& i == map->pos.x)
				ft_put_char_colored('-', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
			/* every other separator, hidden */
			else
				ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
		}
	}

	ft_put_char_colored('\n', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
}

/* print one single line - not the separator */
void ft_print_line_one(t_map *map, int currentLine)
{
	int i, j;

	for (i = 0; i < map->size.x; ++i)
	{
		/* white separator */
		if (ft_explode_bubble(map, currentLine, i, COLOR_WHITE, COUNT_AROUND_START) >= 2
			&& (currentLine == 0 || currentLine == SCREEN_HEIGHT-1) && i != 0)
			ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
		/* white separator bubbles at the edge */
		else if ((i == map->pos.x || i == map->pos.x + 1) && currentLine == map->pos.y)
			ft_put_char_colored('|', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
		/* every other separator, hidden */
		else
			ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);

		/* blocks */
		for (j = 0; j < PIXEL_SIZE; ++j)
			ft_put_char_colored(' ', ATTR_RESET, map->map[currentLine][i], map->map[currentLine][i]);
	}

	ft_put_char_colored('\n', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
}

/*
	print a single char, with custom attribut / background color / foreground color
	see constantes.h for all available colors and attributs
	nb : the term must be ANSI compliant to show the expected result
*/
void ft_put_char_colored(char c, int attr, int fg, int bg)
{
	char command[15];

	sprintf(command, "\x1b[%d;%d;%dm", attr, fg + 30, bg + 40);
	printf("%s", command);
	if (c != 0)
		printf("%c", c);
}


/*============================================================================*/

/* please read another function, this one is *really* hardcore */

#ifndef MAGIC_NUMBER
	#define MAGIC_NUMBER 18
#endif

void ft_print_score(t_map *map)
{
	int i, j;

	ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	for (i = 0; i < PIXEL_SIZE; ++i)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
	for (i = 0; i < (map->size.x-2)*(PIXEL_SIZE+1)+1; ++i)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	for (i = 0; i < PIXEL_SIZE; ++i)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
	ft_put_char_colored('\n', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);


	ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	for (j = 0; j < PIXEL_SIZE; ++j)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
	for (j = 0; j < MAGIC_NUMBER; ++j)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	printf("SCORE : %3d %3s", map->score, map->score > 1 ? "pts" : "pt");
	for (j = 0; j < MAGIC_NUMBER; ++j)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	for (j = 0; j < PIXEL_SIZE; ++j)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
	ft_put_char_colored('\n', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);


	ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	for (i = 0; i < PIXEL_SIZE; ++i)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
	for (i = 0; i < (map->size.x-2)*(PIXEL_SIZE+1)+1; ++i)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	for (i = 0; i < PIXEL_SIZE; ++i)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
	ft_put_char_colored('\n', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);

	ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	for (i = 0; i < map->size.x*(PIXEL_SIZE+1)-1; ++i)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
	ft_put_char_colored('\n', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);

	ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
	for (i = 0; i < map->size.x*(PIXEL_SIZE+1)-1; ++i)
		ft_put_char_colored(' ', ATTR_RESET, COLOR_WHITE, COLOR_WHITE);
	ft_put_char_colored('\n', ATTR_RESET, COLOR_WHITE, COLOR_BLACK);
}

