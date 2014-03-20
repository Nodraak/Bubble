/* 
* @Author: Adrien Chardon
* @Date:   2014-02-14 19:18:59
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-20 18:19:35
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> /* usleep */

#include "constantes.h"
#include "play.h"
#include "AsyncInput.h"
#include "print.h"
#include "init.h"

/* main loop */
void ft_play(t_keymap *keymap)
{
	int quit = 0, tick = 0;
	t_map map;

	/* init */
	ft_init_map(&map);

	/* main loop */
	while (!quit && map.bubbles_left != 0)
	{
		/* get event and handle them */
		ft_handle_event(&map, keymap, &quit);

		/* update bubbles pos - if needed */
		if (tick % (BLOCK_MOVE_DELAY/(1000/FPS)) == 0)
			ft_update_bubble(&map);

		/* refresh screen - if needed */
		if (tick % (SCREEN_REFRESH_DELAY/(1000/FPS)) == 0)
		{
			ft_print_map(&map);
			ft_print_score(&map);
		}

		/* be cpu-nice + frame counter */
		usleep(1000*1000/FPS);
		tick++;
	}

	/* game win event, not user quit event */
	if (map.bubbles_left == 0)
	{
		printf("\nBravo ! Vous avez gagne !!\n");
		usleep(1000*1000);
	}

	/* cleanup */
	ft_free_map(&map);
}

/* update selected bubble and check if going out range + handle fire an quit */
void ft_handle_event(t_map *map, t_keymap *keymap, int *quit)
{
	while (kbhit())
	{
		char c = getchar();

		if (c == keymap->quit)
			*quit = 1;

		if (c == keymap->enter)
			ft_fire(map);

		if (c == keymap->left)
			map->pos.x--;
		if (c == keymap->right)
			map->pos.x++;
		if (c == keymap->up)
			map->pos.y--;
		if (c == keymap->down)
			map->pos.y++;

		if (map->pos.x < 1)
			map->pos.x = 1;
		if (map->pos.x > SCREEN_WIDTH-2)
			map->pos.x = SCREEN_WIDTH-2;
		if (map->pos.y < 1)
			map->pos.y = 1;
		if (map->pos.y > SCREEN_HEIGHT-2)
			map->pos.y = SCREEN_HEIGHT-2;
	}
}

/* return the nb of bubble of the same color aroud and/or explode it */
int ft_explode_bubble(t_map *map, int y, int x, int id, int explode)
{
	int n = 0;
	int newExplode;

	/* in screen area */
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT && id != COLOR_BLACK)
	{
		/* same color -> able to explode */
		if (map->map[y][x] == id)
		{
			n++;
			
			/* if request to explode */
			if (explode == EXPLODE)
			{
				map->bubbles_left--;
				map->map[y][x] = COLOR_BLACK;

				newExplode = EXPLODE;
			}
			/* if only request the number (for printf purpose) */
			else if (explode == COUNT_AROUND_START)
			{
				newExplode = COUNT_AROUND_END;
			}
			/* no recursion needed, return */
			else
			{
				return n;
			}

			n += ft_explode_bubble(map, y, x+1, id, newExplode);
			n += ft_explode_bubble(map, y, x-1, id, newExplode);
			n += ft_explode_bubble(map, y+1, x, id, newExplode);
			n += ft_explode_bubble(map, y-1, x, id, newExplode);
		}
	}

	return n;
}

/* explode a bubble and the same colored ones around + update score */
void ft_fire(t_map *map)
{
	int nb;

	nb = ft_explode_bubble(map, map->pos.y, map->pos.x, map->map[map->pos.y][map->pos.x], EXPLODE);
	map->score += nb*(nb+1)/2;
}

/* the gravity makes bubbles falling - yeah, like newton's apple */
void ft_update_bubble(t_map *map)
{
	int i, j;

	/* for each column */
	for (i = 0; i < map->size.x; ++i)
	{
		/* for each bubble of the column */
		for (j = map->size.y-1; j > 0; --j)
		{
			if (map->map[j][i] == COLOR_BLACK && map->map[j-1][i] != COLOR_WHITE)
			{
				map->map[j][i] = map->map[j-1][i];
				map->map[j-1][i] = COLOR_BLACK;
			}
		}
	}
}

