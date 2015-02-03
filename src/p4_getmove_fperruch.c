/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p4_getmove_<yourlogin>.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gallard <gallard@student.42.fr             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 16:13:55 by gallard           #+#    #+#             */
/*   Updated: 2015/02/03 15:45:20 by fdaudre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puiss4.h"
#define MAX_DEPTH		6

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

static int				get_scoremax(int score[GRID_W], size_t depth, int is_same)
{
	int					max;
	int					i;
	int					col;

	i = 0;
	max = score[0];
	col = 0;
	while (++i < GRID_W)
	{
//		if (!is_same ? (score[i] < max) : (score[i] > max))
		if ((score[i] >= max) && (abs(col - 3) > abs(i - 3)))
		{
			max = score[i];
			col = i;
		}
	}
	return (!depth ? col : max);
	(void)is_same;
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

static int				recursive(t_grid *grid, t_case my_color, t_case color,
							size_t depth)
{
	int					col;
	int					row;
	int					score[GRID_W];

	if (depth >= MAX_DEPTH)
		return (0);
	col = -1;
	while (++col < GRID_W)
	{
		if ((row = get_row(grid, col)) < 0)
		{
			score[col] = -1000000;
			continue ;
		}
		(*grid)[row][col] = color;
		score[col] = calc_score(grid, row, col, color) * (MAX_DEPTH - depth);
//		if (color != my_color)
//			score[col] = -score[col];
//		else
//			score[col] += (0 + abs(col - 3));
//printf("[%lu] -- col: %d => score: %d\n", depth, col, score[col]);
//		if ((score[col] > 9) && (!depth))
//			return (col);
//	p4_disp(grid);
//	printf("SCORE: %d\n", score[col]);
		score[col] += recursive(grid, my_color,
				(color == ROUGE ? JAUNE : ROUGE), depth + 1);
		(*grid)[row][col] = VIDE;
	}
//printf("depth: %lu -- %d, %d, %d, %d, %d, %d, %d\n", depth, score[0], score[1], score[2], score[3], score[4], score[5], score[6]);
	int max = (get_scoremax(score, depth, color == my_color));
//printf("~~ max: %d\n", max);
	return max;
	return (get_scoremax(score, depth, color == my_color));
}

int						p4_getmove_fperruch(t_grid *grid, t_case color,
							int turn_count)
{
	int					move;

	
	move = recursive(grid, color, color, 0);
	return (move);
	(void)turn_count;
}
