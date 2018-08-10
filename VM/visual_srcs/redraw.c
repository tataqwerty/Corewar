/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:12:17 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:12:19 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	compute_speed(t_win *win, int key)
{
	if (key == KEY_Q || key == KEY_W)
	{
		if (key == KEY_Q && win->speed > 10)
			win->speed -= 10;
		else if (key == KEY_W && win->speed > 1)
			win->speed -= 1;
		else
			win->speed = 1;
	}
	else if (key == KEY_E || key == KEY_R)
	{
		if (key == KEY_R && win->speed < 990)
			win->speed += 10;
		else if (key == KEY_E && win->speed < 1000)
			win->speed += 1;
		else
			win->speed = 1000;
	}
	wattron(win->window, COLOR_PAIR(7) | A_BOLD);
	mvwprintw(win->window, CURSOR_Y + 2, CURSOR_X + win->sidebar_pad + 22,
	"%-4d", win->speed);
	wattroff(win->window, COLOR_PAIR(7) | A_BOLD);
}

static void	dispatcher_keys(t_win *win, int key)
{
	if (key == RESIZE)
		prepare_window(win);
	else if (key == KEY_SPACE)
	{
		if (win->paused)
		{
			nodelay(stdscr, true);
			win->paused = 0;
		}
		else
		{
			nodelay(stdscr, false);
			win->paused = 1;
		}
		show_status(win);
	}
	else if (key == KEY_Q || key == KEY_W || key == KEY_E || key == KEY_R)
		compute_speed(win, key);
}

void		redraw(t_win *win)
{
	int		key;
	clock_t	start;

	start = clock();
	while (!g_vm->winner && (key = getch()) != 3)
	{
		if (key != -1)
			dispatcher_keys(win, key);
		win->cursor_x = X_BEGIN;
		win->cursor_y = Y_BEGIN;
		if (key == KEY_S || (!win->paused && (clock() - start > SPEED)))
		{
			start = clock();
			step();
			draw_map(win);
			handle_pixels();
		}
		show_sidebar(win);
		wrefresh(win->window);
	}
	(g_vm->winner) ? print_winner(win) : 0;
	wrefresh(win->window);
	nodelay(stdscr, false);
	(g_vm->winner) ? getch() : 0;
}
