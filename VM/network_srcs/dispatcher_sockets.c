/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_sockets.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:15:01 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:15:02 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	accept_client(t_server *server)
{
	unsigned char	i;
	int				new_socket;

	new_socket = accept(server->master_socket, NULL, NULL);
	(!new_socket) ? ft_error(ERR_303) : 0;
	if (g_vm->count_players >= 4)
	{
		close(new_socket);
		return ;
	}
	i = 0;
	while (i < server->n_client_sockets)
	{
		if (server->client_sockets[i] == 0)
		{
			server->client_sockets[i] = new_socket;
			g_vm->count_players++;
			send(new_socket, "OK", 2, 0);
			return ;
		}
		i++;
	}
}

static void	check_clients(t_server *server)
{
	int				sd;
	unsigned char	i;

	i = 0;
	while (i < server->n_client_sockets)
	{
		sd = server->client_sockets[i];
		if (FD_ISSET(sd, &server->read_fds))
		{
			if (read(sd, 0, 0) < 0)
			{
				g_vm->count_players--;
				server->client_sockets[i] = 0;
				close(sd);
			}
		}
		i++;
	}
}

/*
** FD_ISSET checks whether someone wants to connect to the server.
*/

void		dispatcher_sockets(t_server *server)
{
	if (FD_ISSET(server->master_socket, &server->read_fds))
		accept_client(server);
	else
		check_clients(server);
}
