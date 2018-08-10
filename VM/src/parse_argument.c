/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:09:01 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:09:02 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		get_dump(char **args, int count, int *i)
{
	(*i)++;
	if (*i < count && ft_is_uint(args[*i]))
	{
		g_vm->flag_dump = 1;
		g_vm->dump_cycles = ft_atoi(args[*i]);
	}
	else
		usage();
}

static void		get_bot(unsigned int id, char *filename)
{
	int			fd;
	t_bot		*new;

	g_vm->count_players++;
	if (g_vm->count_players > 4)
		ft_error(ERR_111);
	if ((fd = open(filename, O_RDONLY)) < 0 || read(fd, 0, 0) == -1)
		ft_error(ERR_112);
	new = push_new_bot(&g_vm->bot, id);
	bot_parsing(fd, new);
	close(fd);
}

static void		get_number_bot(char **args, int count, int *i)
{
	unsigned int	id;

	(*i)++;
	if (*i < count && ft_is_uint(args[*i]))
	{
		id = ft_atoi(args[*i]);
		(*i)++;
		(*i < count) ? get_bot(id * -1, args[*i]) : usage();
	}
	else
		usage();
}

static char		available_id(unsigned int id)
{
	t_bot		*bot;

	bot = g_vm->bot;
	while (bot)
	{
		if (bot->id == id)
			return (0);
		bot = bot->next;
	}
	return (1);
}

void			parse_argument(int count, char **args, int *i)
{
	unsigned int	id;

	id = -1;
	if (ft_strequ(args[*i], "-dump"))
		get_dump(args, count, i);
	else if (ft_strequ(args[*i], "-n"))
		get_number_bot(args, count, i);
	else if (ft_strequ(args[*i], "-v"))
		g_vm->flag_visual = 1;
	else if (ft_strequ(args[1], "-s") && count == 3)
		get_info_server(args, count, i);
	else if (ft_strequ(args[*i], "-c") && count == 4)
		get_info_client(args, count, i);
	else
	{
		while (!available_id(id))
			id--;
		get_bot(id, args[*i]);
	}
}
