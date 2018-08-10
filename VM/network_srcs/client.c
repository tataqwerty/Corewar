/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 18:14:55 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 18:14:57 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_connection(int socket_fd)
{
	char	buffer[3];

	ft_bzero(buffer, 3);
	if (read(socket_fd, buffer, 2) != 2 || !ft_strequ(buffer, "OK"))
	{
		close(socket_fd);
		ft_error(ERR_301);
	}
}

static void	connect_to_server(int socket_fd, char *ip)
{
	struct sockaddr_in	address;
	struct timeval		timeout;
	fd_set				set;

	fcntl(socket_fd, F_SETFL, O_NONBLOCK);
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT);
	if (!inet_aton(ip, &address.sin_addr))
		ft_error(ERR_301);
	connect(socket_fd, (struct sockaddr *)&address, sizeof(address));
	FD_ZERO(&set);
	FD_SET(socket_fd, &set);
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	if (select(socket_fd + 1, &set, NULL, NULL, &timeout) != 1)
		ft_error(ERR_301);
	check_connection(socket_fd);
}

static void	read_init_info(int socket_fd, fd_set read_fds)
{
	unsigned char	str[2];

	while (1)
	{
		ft_bzero(str, 2);
		get_data_select(socket_fd, read_fds, &str[0], 1);
		get_data_select(socket_fd, read_fds, &str[1], 1);
		system("clear");
		ft_printf("{blue}Time to start the game:{red} %d\n", str[0]);
		ft_printf("{blue}Number of connected players:{green} %d\n", str[1]);
		if (str[0] == 0)
			break ;
		sleep(1);
	}
}

/*
** send name | comment | size | exec
*/

static void	serialize(t_bot *bot, unsigned char *str)
{
	unsigned char size[4];

	size[0] = ((unsigned char *)&bot->size)[0];
	size[1] = ((unsigned char *)&bot->size)[1];
	size[2] = ((unsigned char *)&bot->size)[2];
	size[3] = ((unsigned char *)&bot->size)[3];
	ft_memcpy(str, bot->name, PROG_NAME_LENGTH);
	ft_memcpy(str + PROG_NAME_LENGTH, bot->comment, COMMENT_LENGTH);
	ft_memcpy(str + PROG_NAME_LENGTH + COMMENT_LENGTH, size, 4);
	ft_memcpy(str + PROG_NAME_LENGTH + COMMENT_LENGTH + 4,
		bot->exec, bot->size);
}

void		client(void)
{
	int				len;
	int				socket_fd;
	unsigned char	s[PROG_NAME_LENGTH + COMMENT_LENGTH + g_vm->bot->size + 4];
	fd_set			read_fds;

	len = PROG_NAME_LENGTH + COMMENT_LENGTH + g_vm->bot->size + 4;
	(g_vm->count_players != 1) ? ft_error(ERR_302) : 0;
	ft_bzero(s, len);
	socket_fd = create_socket();
	connect_to_server(socket_fd, g_vm->ip);
	FD_SET(socket_fd, &read_fds);
	read_init_info(socket_fd, read_fds);
	serialize(g_vm->bot, s);
	send(socket_fd, s, len, 0);
	get_game(socket_fd, read_fds);
	FD_ZERO(&read_fds);
	close(socket_fd);
}
