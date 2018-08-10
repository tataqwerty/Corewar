/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar_statistics.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:12:33 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:12:34 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static double	get_cost_live(t_bot *bot, char len, char flag)
{
	double	res;

	res = 0;
	while (bot)
	{
		if (flag == CURR_PERIOD)
			res += bot->lives_cur_period;
		else if (flag == LAST_PERIOD)
			res += bot->lives_last_period;
		bot = bot->next;
	}
	if (res == 0)
		return (0);
	return ((double)len / res);
}

static int		ft_round(double n)
{
	int res;

	res = (int)n;
	n -= (double)res;
	if (n >= 0.5)
		return (res + 1);
	else
		return (res);
}

static void		show_line(t_win *win, t_bot *bot, char flag)
{
	double			cost_live;
	int				tmp;
	char			len;

	len = 50;
	cost_live = get_cost_live(bot, len, flag);
	mvwaddch(win->window, CURSOR_Y, CURSOR_X, '[');
	CURSOR_X++;
	mvwaddch(win->window, CURSOR_Y, CURSOR_X + len, ']');
	while (len > 0)
		mvwaddch(win->window, CURSOR_Y, CURSOR_X + --len, '-');
	while (bot)
	{
		if (flag == CURR_PERIOD)
			tmp = ft_round(cost_live * bot->lives_cur_period);
		else
			tmp = ft_round(cost_live * bot->lives_last_period);
		wattron(win->window, COLOR_PAIR(bot->player_counter));
		while (tmp-- > 0 && len++ < 50)
			mvwaddch(win->window, CURSOR_Y, CURSOR_X++, '-');
		wattroff(win->window, COLOR_PAIR(bot->player_counter));
		bot = bot->next;
	}
	CURSOR_X = win->sidebar_pad + X_BEGIN;
}

void			sidebar_statistics(t_win *win)
{
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"Live breakdown for current period : ");
	CURSOR_Y++;
	wattron(win->window, COLOR_PAIR(5));
	show_line(win, g_vm->bot, CURR_PERIOD);
	wattroff(win->window, COLOR_PAIR(5));
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"Live breakdown for last period : ");
	CURSOR_Y++;
	wattron(win->window, COLOR_PAIR(5));
	show_line(win, g_vm->bot, LAST_PERIOD);
	wattroff(win->window, COLOR_PAIR(5));
	CURSOR_Y += 2;
}
