/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p4_getmove_<yourlogin>.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gallard <gallard@student.42.fr             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 16:13:55 by gallard           #+#    #+#             */
/*   Updated: 2015/02/03 12:02:25 by fdaudre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puiss4.h"

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

int		p4_getmove_fperruch(t_grid *grid, t_case color, int turn_count)
{
	int		move;

	(void)grid;
	(void)color;
	(void)turn_count;
	move = 0;

	// TODO: find out what's the best move toward winning the game

	return (move);
}

int		p4_getmove_yourlogin(t_grid *grid, t_case color, int turn_count)
{
	int		move;

	(void)grid;
	(void)color;
	(void)turn_count;
	move = 0;

	// TODO: find out what's the best move toward winning the game

	return (move);
}
