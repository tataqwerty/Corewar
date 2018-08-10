/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clients.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:15:11 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:15:12 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		add_sockets_to_set(t_server *server, int *max_sd)
{
	unsigned char	i;
	int				sd;

	i = 0;
	FD_ZERO(&server->read_fds);
	FD_SET(server->master_socket, &server->read_fds);
	*max_sd = server->master_socket;
	while (i < server->n_client_sockets)
	{
		sd = server->client_sockets[i];
		if (sd != 0)
		{
			FD_SET(sd, &server->read_fds);
			if (*max_sd < sd)
				*max_sd = sd;
		}
		i++;
	}
}

static void		*apply_clients(void *data)
{
	t_server		*server;
	struct timeval	timeout;
	int				activity;
	int				max_sd;

	server = (t_server *)data;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	max_sd = 0;
	while (!server->flag_start)
	{
		add_sockets_to_set(server, &max_sd);
		activity = select(max_sd + 1, &server->read_fds, NULL, NULL, &timeout);
		(activity < 0) ? ft_error(ERR_305) : 0;
		dispatcher_sockets(server);
	}
	(g_vm->count_players == 0) ? ft_error(ERR_304) : 0;
	return (data);
}

static void		*send_init_info_to_players(void *data)
{
	char		sec;
	t_server	*server;

	sec = 30;
	server = (t_server *)data;
	while (sec >= 0)
	{
		sleep(1);
		foreach_sockets(server, (unsigned char *)&sec, sizeof(unsigned char));
		foreach_sockets(server, &g_vm->count_players, sizeof(unsigned char));
		system("clear");
		ft_printf("{blue}Time to start the game:{red} %d\n", sec);
		ft_printf("{blue}Number of connected players:{green} %d\n",
					g_vm->count_players);
		sec--;
	}
	server->flag_start = 1;
	return (data);
}

void			get_clients(t_server *server)
{
	pthread_t	tid[2];

	pthread_create(&tid[0], NULL, send_init_info_to_players, server);
	pthread_create(&tid[1], NULL, apply_clients, server);
	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	get_clients_exec(server);
}
