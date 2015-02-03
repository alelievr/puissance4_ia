/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_dev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gallard <gallard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/09/27 16:13:55 by gallard           #+#    #+#             */
/*   Updated: 2015/02/03 15:11:48 by fdaudre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puiss4.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int		p4_getmove_fperruch(t_grid *grid, t_case color, int turn_count);

int		main(void)
{
	t_grid		grid;
	int			move;
	int			i;

	setlocale(LC_ALL, "");

	p4_init(&grid);
	printf("Vous avez les jaunes !\n");
	p4_disp(&grid);
	
	i = 0;
	while (1)
	{
		srand(time(0));
		// Block: Human
		printf("0 1 2 3 4 5 6\nJouer [1-7]: ");
		scanf("%d", &move);
//		--move;
	//	puts("Au JAUNE (votre IA):");
	//	move = p4_getmove_fperruch(&grid, ROUGE, i);
		p4_play(&grid, move, JAUNE);
		p4_disp(&grid);
		if (p4_won(&grid, move))
		{
			puts("YOU WON!");
			break ;
		}
		i++;

		// Block: AI
		puts("Au ROUGE (votre IA):");
		move = p4_getmove_fperruch(&grid, ROUGE, i);
		p4_play(&grid, move, ROUGE);
		p4_disp(&grid);
		if (p4_won(&grid, move))
		{
			puts("COMPUTER WON!");
			break ;
		}
		i++;
	}
	return (0);
}
