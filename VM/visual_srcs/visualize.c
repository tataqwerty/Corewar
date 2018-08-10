/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/22 16:02:56 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/22 16:02:58 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** line 32: '3' - is a CTRL + C
*/

void	visualize(void)
{
	t_win	*win;

	create_pixel_map();
	fill_pixel_map();
	initscr();
	noecho();
	raw();
	color_preparation();
	win = init_win();
	if (g_vm->flag_dump)
		while (g_vm->cur_cycle < g_vm->dump_cycles && !g_vm->winner)
		{
			step();
			handle_pixels();
		}
	prepare_window(win);
	redraw(win);
	delwin(win->window);
	endwin();
	free(win);
}
