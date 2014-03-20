/* 
* @Author: Adrien Chardon
* @Date:   2014-02-20 17:22:21
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-20 18:07:57
*/

#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "init.h"

/* init keyboard configuration */
void ft_init_keymap(t_keymap *keymap)
{
	keymap->up = 'z';
	keymap->down = 's';
	keymap->left = 'q';
	keymap->right = 'd';
	
	keymap->enter = 'f';
	keymap->quit = 'p';
}

/* init main struct */
void ft_init_map(t_map *map)
{
	int i, j;

	map->size.x = SCREEN_WIDTH;
	map->size.y = SCREEN_HEIGHT;

	map->pos.x = map->size.x/2;
	map->pos.y = map->size.y/2;

	map->score = 0;
	map->bubbles_left = (map->size.x-2) * (map->size.x-2);

	map->map = malloc(sizeof(int*) * map->size.y);
	for (j = 0; j < map->size.y; ++j)
	{
		map->map[j] = malloc(sizeof(int) * map->size.x);

		for (i = 0; i < map->size.x; ++i)
		{
			if (i == 0 || i == SCREEN_WIDTH-1 || j == 0 || j == SCREEN_HEIGHT-1)
				map->map[j][i] = COLOR_WHITE;
			else
				map->map[j][i] = (rand()%(COLOR_LAST-2))+1;
		}
	}
}

/* free the allocated struct */
void ft_free_map(t_map *map)
{
	int i;

	for (i = 0; i < map->size.y; ++i)
		free(map->map[i]);
	free(map->map);
}
