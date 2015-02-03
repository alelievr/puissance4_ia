/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_score.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaudre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 13:03:28 by fdaudre-          #+#    #+#             */
/*   Updated: 2015/02/03 15:41:47 by fdaudre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puiss4.h"

//#if 0
static int		calc_score_hz(t_grid *grid, int col, int row, t_case color)
{
	int		i;
	int		count;

	count = 1;
	i = col;
	while (--i >= 0)
	{
		if ((*grid)[row][i] == color)
			count++;
		else
			break;
	}
	i = col;
	while (++i < GRID_W)
	{
		if ((*grid)[row][i] == color)
			count++;
		else
			break;
	}
	return (count >= WIN_CNT);
}

static int		calc_score_vz(t_grid *grid, int col, int row, t_case color)
{
	int		i;
	int		count;

	count = 1;
/*	i = row;
	while (--i >= 0)
	{
		if ((*grid)[i][col] == color)
			count++;
		else
			break;
	}*/
	i = row;
	while (++i < GRID_H)
	{
		if ((*grid)[i][col] == color)
			count++;
		else
			break;
	}
	return (count >= WIN_CNT);
}
//#endif

static int		calc_score_diag1(t_grid *grid, int col, int row, t_case color)
{
	int		i;
	int		count;

	count = 1;
	i = 1;
	while ((col + i) < GRID_W && (row + i) < GRID_H)
	{
		if ((*grid)[row + i][col + i] == color)
			count++;
		else
			break;
		i++;
	}
	i = -1;
	while ((col + i) >= 0 && (row + i) >= 0)
	{
		if ((*grid)[row + i][col + i] == color)
			count++;
		else
			break;
		i--;
	}
	return (count >= WIN_CNT);
}

static int		calc_score_diag2(t_grid *grid, int col, int row, t_case color)
{
	int		i;
	int		count;

	count = 1;
	i = 1;
	while ((col + i) < GRID_W && (row - i) >= 0)
	{
		if ((*grid)[row - i][col + i] == color)
			count++;
		else
			break;
		i++;
	}
	i = 1;
	while ((col - i) >= 0 && (row + i) < GRID_H)
	{
		if ((*grid)[row + i][col - i] == color)
			count++;
		else
			break;
		i++;
	}
	return (count >= WIN_CNT);
}
/*
static int				calc_score_hz(t_grid *grid, int row, int col, t_case color)
{
	int					i;
}*/

int						calc_score(t_grid *grid, int row, int col, t_case color)
{
	int					score;

	score = calc_score_hz(grid, row, col, color) +
			calc_score_vz(grid, row, col, color) +
			calc_score_diag1(grid, row, col, color) +
			calc_score_diag2(grid, row, col, color);
	score *= 10;
	return (score);
}
