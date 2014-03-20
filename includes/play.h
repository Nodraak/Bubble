/* 
* @Author: Adrien Chardon
* @Date:   2014-02-14 19:19:29
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-20 17:48:25
*/

#ifndef PLAY_H
#define PLAY_H

void ft_play(t_keymap *keymap);
void ft_handle_event(t_map *map, t_keymap *keymap, int *quit);
int ft_explode_bubble(t_map *map, int y, int x, int id, int explode);
void ft_fire(t_map *map);
void ft_update_bubble(t_map *map);

#endif
