/* 
* @Author: Adrien Chardon
* @Date:   2014-02-22 22:16:44
* @Last Modified by:   Adrien Chardon
* @Last Modified time: 2014-02-22 22:35:48
*/

#include <stdlib.h>
#include <stdio.h>

#include "constantes.h"
#include "score.h"

void ft_print_scores(void)
{
	char data[1024];

	ft_get_score(data);

	clear_screen();
	
	printf(	"+---------------------+\n"
			"|       SCORES        |\n"
			"+---------------------+\n"
			"\n"
			"%s"
			"\n"
			"Appuyer sur une touche pour continuer.\n",
			data);

	getchar();
}

void ft_get_score(char *s)
{
	FILE *f = fopen("data.bin", "r");

	if (f == NULL)
	{
		sprintf(s, "Cant open file (%s:%d).\n", __FILE__, __LINE__);
	}
	else
	{
		char names[3][1024];
		int score[3], i;

		for (i = 0; i < 3; ++i)
			fscanf(f, "%d %s", &score[i], names[i]);

		sprintf(s,	"| Pts | Pseudo |\n"
					"+-----+--------+\n"
					"| %3d | %6s |\n"
					"| %3d | %6s |\n"
					"| %3d | %6s |\n"
					"+-----+--------+\n",
					score[0], names[0],
					score[1], names[1],
					score[2], names[2]);
	
		fclose(f);
	}
}