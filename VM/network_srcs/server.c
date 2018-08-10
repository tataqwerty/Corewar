/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:15:45 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:15:47 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			bzero_sockets(int sockets[], int n_sockets)
{
	int i;

	i = 0;
	while (i < n_sockets)
		sockets[i++] = 0;
}

static t_server		*init_server(void)
{
	t_server *server;

	server = (t_server *)malloc(sizeof(t_server));
	(!server) ? ft_error(ERR_101) : 0;
	server->master_socket = create_socket();
	server->n_client_sockets = 4;
	bzero_sockets(server->client_sockets, server->n_client_sockets);
	server->flag_start = 0;
	return (server);
}

static char			bind_to_address(int socket_fd, char *ip)
{
	struct sockaddr_in address;

	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error(ERR_307);
	return (bind(socket_fd, (struct sockaddr *)&address,
			sizeof(struct sockaddr_in)));
}

static void			close_sockets(t_server *server)
{
	unsigned char i;

	i = 0;
	while (i < server->n_client_sockets)
	{
		if (server->client_sockets[i] > 0)
			close(server->client_sockets[i]);
		i++;
	}
	close(server->master_socket);
}

void				server(void)
{
	t_server *server;

	server = init_server();
	(bind_to_address(server->master_socket, g_vm->ip))
		? ft_error(ERR_308) : 0;
	listen(server->master_socket, 1);
	get_clients(server);
	fill_map();
	create_pixel_map();
	fill_pixel_map();
	send_data_all_clients(server);
	close_sockets(server);
	free(server);
}
