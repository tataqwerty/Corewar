/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual_staff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:12:40 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:12:41 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_winner(t_win *win)
{
	wattron(win->window, A_BOLD);
	mvwprintw(win->window, CURSOR_Y, CURSOR_X, "The winner is : ");
	wattron(win->window, COLOR_PAIR(g_vm->winner->player_counter));
	mvwprintw(win->window, CURSOR_Y, CURSOR_X + 16, "%s", g_vm->winner->name);
	wattroff(win->window, COLOR_PAIR(g_vm->winner->player_counter));
	mvwprintw(win->window, CURSOR_Y + 2, CURSOR_X, "Press any key to finish");
	wattroff(win->window, A_BOLD);
}

void	handle_pixels(void)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (g_pixels[i]->counter > 0)
		{
			g_pixels[i]->counter--;
			if (g_pixels[i]->counter == 0 && g_pixels[i]->color / 10 != 2)
				g_pixels[i]->color %= 10;
		}
		i++;
	}
}
