/* 
* @Author: Adrien Chardon
* @Date:   2014-02-14 13:39:11
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-15 15:28:24
*/

#ifndef PRINT_H
#define PRINT_H

void ft_print_score(t_map *map);

void ft_print_map(t_map *map);
void ft_print_sep_horiz(t_map *map, int currentLine);
void ft_print_line_one(t_map *map, int currentLine);
void ft_put_char_colored(char c, int attr, int fg, int bg);

#endif
