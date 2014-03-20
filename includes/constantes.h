/* 
* @Author: Adrien Chardon
* @Date:   2014-02-14 09:58:53
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-20 18:08:02
*/

#ifndef CONSTANTES_H
#define CONSTANTES_H

/*=== DEFINE ===*/
/* frames per second - computed ones, not printed ones -> see screen_refresh_delay */
#define FPS						20
#define BLOCK_MOVE_DELAY		500			/* time in ms for one block to move */
#define SCREEN_REFRESH_DELAY	(1000/10)	/* must be lower than BLOCK_MOVE_DELAY */

/* screen size, in bubbles, minus 2 for edges */
#define SCREEN_WIDTH			12
#define SCREEN_HEIGHT			12

#define PIXEL_SIZE				4			/* width size of bubbles */

#define clear_screen()			printf("\e[1;1H\e[2J")

/*=== STRUCT ===*/
typedef struct 	s_vector
{
	int			x;
	int			y;
}				t_vector;

typedef struct 	s_map
{
	char		**map;			/* malloc-ed map */
	t_vector	size;			/* size of the map - used by malloc */
	t_vector	pos;			/* coord of the selected bubble */
	int			score;			/* number of points */
	int			bubbles_left;	/* number of bubbles left, used to know when the game ends */
}				t_map;

/* keyboard configuration */
typedef struct 	s_keymap
{
	int			up;
	int			down;
	int			left;
	int			right;

	int			enter;
	int			quit;
}				t_keymap;

/*=== ENUM - for term color ===*/
enum e_attr
{
	ATTR_RESET = 0,
	ATTR_BRIGHT,
	ATTR_DIM,
	ATTR_UNDERLINE,
	ATTR_BLINK,
	ATTR_REVERSE,
	ATTR_HIDDEN
};

enum e_color
{
	COLOR_BLACK = 0,
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_MAGENTA,
	COLOR_CYAN,
	COLOR_WHITE,
	COLOR_LAST
};

/* very bad : anonymous enum */
enum
{
	EXPLODE,
	COUNT_AROUND_START,
	COUNT_AROUND_END
};

#endif
