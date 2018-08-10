/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clients_exec.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 18:11:43 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/01 18:11:44 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		get_clients_exec(t_server *server)
{
	int				i;
	int				sd;
	unsigned int	id_bot;
	t_bot			*new_bot;

	i = 0;
	id_bot = -1;
	while (i < server->n_client_sockets)
	{
		sd = server->client_sockets[i];
		if (sd > 0)
		{
			new_bot = push_new_bot(&g_vm->bot, id_bot);
			new_bot->player_counter = i + 1;
			read(sd, &new_bot->name, PROG_NAME_LENGTH);
			read(sd, &new_bot->comment, COMMENT_LENGTH);
			read(sd, &new_bot->size, 4);
			new_bot->exec = (unsigned char *)malloc(new_bot->size);
			ft_bzero(new_bot->exec, new_bot->size);
			read(sd, new_bot->exec, new_bot->size);
		}
		id_bot--;
		i++;
	}
}
