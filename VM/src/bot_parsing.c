/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:09:56 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:09:57 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			get_name(int fd, t_bot *new)
{
	unsigned char	buf[4];
	unsigned char	i;

	if (read(fd, &new->name, PROG_NAME_LENGTH) != PROG_NAME_LENGTH)
		ft_error(ERR_108);
	if (read(fd, &buf, 4) != 4)
		ft_error(ERR_107);
	i = 0;
	while (i < 4)
		(buf[i] != 0) ? ft_error(ERR_107) : i++;
}

static void			get_size(int fd, t_bot *new)
{
	if (read(fd, &new->size, 4) != 4)
		ft_error(ERR_115);
	new->size = reverse_bytes(new->size, 4);
	if (new->size > CHAMP_MAX_SIZE || new->size == 0)
		ft_error(ERR_106);
}

static void			get_comment(int fd, t_bot *new)
{
	unsigned char	buf[4];
	unsigned char	i;

	if (read(fd, &new->comment, COMMENT_LENGTH) != COMMENT_LENGTH)
		ft_error(ERR_105);
	if (read(fd, &buf, 4) != 4)
		ft_error(ERR_104);
	i = 0;
	while (i < 4)
		(buf[i] != 0) ? ft_error(ERR_104) : i++;
}

static void			get_executable(int fd, t_bot *new)
{
	unsigned char	tmp[1];

	new->exec = (unsigned char *)malloc(new->size + 1);
	if (!new->exec)
		ft_error(ERR_101);
	if (read(fd, new->exec, new->size) != new->size)
		ft_error(ERR_102);
	if (read(fd, &tmp, 1) != 0)
		ft_error(ERR_103);
}

void				bot_parsing(int fd, t_bot *new)
{
	check_magic_header(fd);
	get_name(fd, new);
	get_size(fd, new);
	get_comment(fd, new);
	get_executable(fd, new);
}
