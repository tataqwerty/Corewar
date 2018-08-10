/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_from_server.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:15:19 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:15:21 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	get_pixel_map(int socket_fd, fd_set read_fds)
{
	int i;

	i = 0;
	while (i < MEM_SIZE)
		get_data_select(socket_fd, read_fds, g_pixels[i++], 2);
}

static void	get_other_data(int socket_fd, fd_set read_fds)
{
	t_bot	*bot;

	get_data_select(socket_fd, read_fds, &g_vm->cycle_to_die, 4);
	get_data_select(socket_fd, read_fds, &g_vm->cur_cycle, 4);
	get_data_select(socket_fd, read_fds, &g_vm->process_count, 4);
	bot = g_vm->bot;
	while (bot)
	{
		get_data_select(socket_fd, read_fds, &bot->lives_cur_period, 4);
		get_data_select(socket_fd, read_fds, &bot->lives_last_period, 4);
		get_data_select(socket_fd, read_fds, &bot->last_live, 4);
		bot = bot->next;
	}
}

static void	get_winner(unsigned int winner_id)
{
	t_bot	*bot;

	bot = g_vm->bot;
	while (bot)
	{
		if (bot->id == winner_id)
		{
			g_vm->winner = bot;
			return ;
		}
		bot = bot->next;
	}
}

void		get_data_from_server(int socket_fd, fd_set read_fds)
{
	unsigned int	winner_id;

	winner_id = 0;
	get_data_select(socket_fd, read_fds, g_map, MEM_SIZE);
	get_pixel_map(socket_fd, read_fds);
	get_other_data(socket_fd, read_fds);
	get_data_select(socket_fd, read_fds, &winner_id, 4);
	(winner_id) ? get_winner(winner_id) : 0;
}
