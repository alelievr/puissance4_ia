/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p4_getmove_<yourlogin>.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gallard <gallard@student.42.fr             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 16:13:55 by gallard           #+#    #+#             */
/*   Updated: 2015/02/03 13:15:22 by fdaudre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puiss4.h"
#define MAX_DEPTH		3

/*
** ------------------------------------------------------------------
** p4_getmove_<yourlogin>(t_grid *grid, t_case color, int turn_count)
** ------------------------------------------------------------------
** t_grid *grid		:		2D array containing ROUGE/JAUNE/VIDE cells
**							it's a copy of the current state of the game
**							(see puiss4.h)
**
** t_case color		:		ROUGE or JAUNE, it's YOUR color
**
** int turn_count	:		number of coins on the grid
**
** return (move)	:		0 <= move < GRID_W
**
** ---------------------
** Available functions :
** ---------------------
** int p4_legal(t_grid *grid, int col)
**		returns 0 if col(umn) is full, 1 if at least one cell is empty
** -
** int p4_won(t_grid *grid, int col);
**		returns 1 if playing in col(umn) will win the game, 0 otherwise
** -
** int p4_play(t_grid *grid, int col, t_case color);
** int p4_unplay(t_grid *grid, int col, t_case color);
**		these 2 functions can help you simulate next moves for both
**		you and your opponent (remember your grid is a copy)
*/

int						calc_score(t_grid *grid, int row, int col, t_case color);

static int				get_scoremax(int score[GRID_W], size_t depth)
{
	int					max;
	int					i;
	int					col;

	i = -1;
	max = -1;
	col = 0;
	while (++i < GRID_W)
	{
		if (score[i] > max)
		{
			max = score[i];
			col = i;
		}
	}
	return (!depth ? col : max);
}

static int				get_row(t_grid *grid, int col)
{
	int					row;

	row = GRID_H;
	while (--row > -1)
	{
		if ((*grid)[row][col] == VIDE)
			break ;
	}
	return (row);
}

#include <stdio.h>
static int				recursive(t_grid *grid, t_case my_color, t_case color,
							size_t depth)
{
	int					col;
	int					row;
	int					score[GRID_W];

printf("tilt\n");
	if (depth >= MAX_DEPTH)
		return (0);
	col = -1;
	while (++col < GRID_W)
	{
//printf("lol\n");
		if ((row = get_row(grid, col)) < 0)
			continue ;
		(*grid)[row][col] = color;
		score[col] = calc_score(grid, row, col, color);
		score[col] += recursive(grid, my_color,
				(color == ROUGE ? JAUNE : ROUGE), depth + 1);
		(*grid)[row][col] = VIDE;
	}
	return (get_scoremax(score, depth));
}

int						p4_getmove_fperruch(t_grid *grid, t_case color,
							int turn_count)
{
	int					move;

	move = recursive(grid, color, color, 0);
	return (move);
	(void)turn_count;
}
