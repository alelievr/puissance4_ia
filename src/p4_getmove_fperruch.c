/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p4_getmove_fperruch.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdaudre- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 17:24:37 by fdaudre-          #+#    #+#             */
/*   Updated: 2015/02/03 17:57:56 by fdaudre-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "puiss4.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_DEPTH		8

static float			ft_rand(int x)
{
    int n = x * 57;
    n = (n << 13) ^ n;
    int t = (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff;
    return (1.0 - (double)t * 0.931322574615478515625e-9);
}


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
		if ((!is_same ? (score[i] < max) : (score[i] > max)) ||
			((score[i] == max) && (ft_rand(rand()) < -.5)))
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

static int				calc_score_hz(t_grid *grid, int row, int col, t_case color)
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

static int				calc_score_vz(t_grid *grid, int row, int col, t_case color)
{
	int		i;
	int		count;

	count = 1;
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

static int				calc_score_diag1(t_grid *grid, int row, int col, t_case color)
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

static int				calc_score_diag2(t_grid *grid, int row, int col, t_case color)
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

static int				calc_score(t_grid *grid, int row, int col, t_case color)
{
	int					score;

	score = calc_score_hz(grid, row, col, color) +
			calc_score_vz(grid, row, col, color) +
			calc_score_diag1(grid, row, col, color) +
			calc_score_diag2(grid, row, col, color);
	score *= (MAX_DEPTH + 2);
	return (score);
}

static int				recursive(t_grid *grid, t_case my_color, t_case color,
							size_t depth)
{
	int					col;
	int					row;
	int					score[GRID_W];
//	int					tmp;

	if (depth >= MAX_DEPTH)
		return (0);
	col = -1;
	while (++col < GRID_W)
	{
		if ((row = get_row(grid, col)) < 0)
		{
			score[col] = -1000000 * (color == my_color ? 1 : -1);
			continue ;
		}
		(*grid)[row][col] = color;
		score[col] = calc_score(grid, row, col, color) * (MAX_DEPTH - depth);
		if (color != my_color)
			score[col] = -score[col];
		if (!depth && (score[col] > 0))
		{
			(*grid)[row][col] = VIDE;
			return (col);
		}
		if (score[col] >= 0)
		{
			score[col] += recursive(grid, my_color,
					(color == ROUGE ? JAUNE : ROUGE), depth + 1);
		}
		else if (depth == 1)
		{
			(*grid)[row][col] = VIDE;
			return (-21345);
		}
		(*grid)[row][col] = VIDE;
	}
	return (get_scoremax(score, depth, color == my_color));
}

int						p4_getmove_fperruch(t_grid *grid, t_case color,
							int turn_count)
{
	int					move;
	int					i;

	move = recursive(grid, color, color, 0);
	if (p4_legal(grid, move))
		return (move);
	i = -1;
	while (++i < GRID_W)
		if (p4_legal(grid, i))
			return (i);
	return (0);
	(void)turn_count;
}
