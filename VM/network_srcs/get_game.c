/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:15:26 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:15:27 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	get_init_data(int socket_fd, fd_set read_fds)
{
	t_bot			*bot;
	unsigned int	bot_id;
	unsigned char	player_counter;

	bot_id = -1;
	player_counter = 1;
	get_data_select(socket_fd, read_fds, &g_vm->count_players, 1);
	while (player_counter <= g_vm->count_players)
	{
		bot = push_new_bot(&g_vm->bot, bot_id);
		bot->player_counter = player_counter;
		get_data_select(socket_fd, read_fds, bot->name, PROG_NAME_LENGTH);
		get_data_select(socket_fd, read_fds, bot->comment, COMMENT_LENGTH);
		bot_id--;
		player_counter++;
	}
}

static void	remove_player(t_bot **bot)
{
	ft_strdel((char **)&(*bot)->exec);
	free(*bot);
	*bot = NULL;
}

void		get_game(int socket_fd, fd_set read_fds)
{
	remove_player(&g_vm->bot);
	create_pixel_map();
	get_init_data(socket_fd, read_fds);
	client_visualize(socket_fd, read_fds);
}
