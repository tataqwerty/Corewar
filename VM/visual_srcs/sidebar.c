/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sidebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:12:25 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:12:27 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		show_status(t_win *win)
{
	wattron(win->window, COLOR_PAIR((win->paused) ? 8 : 9) | A_BOLD);
	mvwprintw(win->window, Y_BEGIN, win->sidebar_pad + X_BEGIN,
			"** %s ** ", ((win->paused) ? "PAUSED" : "RUNNING"));
	wattroff(win->window, COLOR_PAIR((win->paused) ? 8 : 9));
}

static void	sidebar_header(t_win *win)
{
	show_status(win);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"Cycles/second limit : %-4d", win->speed);
	CURSOR_Y += 3;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"Cycle : %d", g_vm->cur_cycle);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"Processes : %-5d", g_vm->process_count);
	CURSOR_Y += 2;
}

static void	sidebar_players(t_win *win)
{
	t_bot	*bot;

	bot = g_vm->bot;
	while (bot)
	{
		mvwprintw(win->window, CURSOR_Y, CURSOR_X,
				"Player %d : ", (int)bot->id);
		wattron(win->window, COLOR_PAIR(bot->player_counter));
		mvwprintw(win->window, CURSOR_Y, CURSOR_X + 12, "%s", bot->name);
		CURSOR_Y++;
		wattroff(win->window, COLOR_PAIR(bot->player_counter));
		mvwprintw(win->window, CURSOR_Y, CURSOR_X,
				"  Last live : %21d", bot->last_live);
		CURSOR_Y++;
		mvwprintw(win->window, CURSOR_Y, CURSOR_X,
				"  Lives in current period : %7d", bot->lives_cur_period);
		CURSOR_Y += 2;
		bot = bot->next;
	}
}

static void	sidebar_footer(t_win *win)
{
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"CYCLE_TO_DIE : %-4u", g_vm->cycle_to_die);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"CYCLE_DELTA : %d", CYCLE_DELTA);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"NBR_LIVE : %d", NBR_LIVE);
	CURSOR_Y += 2;
	mvwprintw(win->window, CURSOR_Y, CURSOR_X,
			"MAX_CHECKS : %d", MAX_CHECKS);
	CURSOR_Y += 2;
}

void		show_sidebar(t_win *win)
{
	win->cursor_y = Y_BEGIN;
	win->cursor_x = win->sidebar_pad + X_BEGIN;
	wattron(win->window, COLOR_PAIR(7) | A_BOLD);
	sidebar_header(win);
	sidebar_players(win);
	sidebar_statistics(win);
	sidebar_footer(win);
	wattroff(win->window, COLOR_PAIR(7) | A_BOLD);
}
