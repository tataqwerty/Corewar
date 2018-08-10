/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:12:11 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:12:12 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	draw_table(t_win *win)
{
	char	c;

	c = '*';
	win->window = newwin(win->height, win->width, 0, 0);
	if (!win->window)
	{
		endwin();
		exit(0);
	}
	wattron(win->window, COLOR_PAIR(6));
	wborder(win->window, c, c, c, c, c, c, c, c);
	mvwvline(win->window, 0, win->sidebar_pad, '*', win->height);
	wattroff(win->window, COLOR_PAIR(6));
}

/*
** line 41: Initial color
*/

static void	attributes_action(WINDOW *window, t_pixel *pixel, char flag)
{
	if (flag == ON)
	{
		wattron(window, COLOR_PAIR(pixel->color));
		if ((pixel->color % 10) == INIT_PIXEL_COLOR)
			wattron(window, A_BOLD);
		else if (pixel->counter > 0)
			wattron(window, A_BOLD);
	}
	else if (flag == OFF)
		wattroff(window, COLOR_PAIR(pixel->color) | A_BOLD);
}

void		draw_map(t_win *win)
{
	char			*base;
	unsigned short	i;

	i = 0;
	base = "0123456789abcdef";
	CURSOR_Y = Y_BEGIN;
	CURSOR_X = X_BEGIN;
	while (i < MEM_SIZE)
	{
		attributes_action(win->window, g_pixels[i], ON);
		mvwaddch(win->window, win->cursor_y, win->cursor_x++,
				base[g_map[i] / 16]);
		mvwaddch(win->window, win->cursor_y, win->cursor_x++,
				base[g_map[i] % 16]);
		attributes_action(win->window, g_pixels[i], OFF);
		i++;
		if ((i % 64) == 0)
		{
			win->cursor_y++;
			win->cursor_x = X_BEGIN;
		}
		else
			mvwaddch(win->window, win->cursor_y, win->cursor_x++, ' ');
	}
}

void		prepare_window(t_win *win)
{
	win->cursor_x = X_BEGIN;
	win->cursor_y = Y_BEGIN;
	clear();
	draw_table(win);
	draw_map(win);
	show_sidebar(win);
	refresh();
	wrefresh(win->window);
}
