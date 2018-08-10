/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:03:16 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/19 14:03:20 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_vm(void)
{
	if (!(g_vm = (t_vm *)malloc(sizeof(t_vm))))
		exit(0);
	ft_bzero(g_map, MEM_SIZE);
	g_vm->count_players = 0;
	g_vm->flag_visual = 0;
	g_vm->flag_dump = 0;
	g_vm->flag_server = 0;
	g_vm->flag_client = 0;
	g_vm->cycle_to_die = CYCLE_TO_DIE;
	g_vm->dump_cycles = 0;
	g_vm->cur_cycle = 0;
	g_vm->process_count = 0;
	g_vm->port = 0;
	g_vm->win_link = NULL;
	g_vm->ip = NULL;
	g_vm->winner = NULL;
	g_vm->process = NULL;
	g_vm->bot = NULL;
	g_vm->last_change_cycle_to_die = 0;
	g_vm->future_die = CYCLE_TO_DIE;
}

void		fill_map(void)
{
	t_bot			*bot;
	unsigned int	i;
	unsigned int	total;

	total = 0;
	bot = g_vm->bot;
	while (bot)
	{
		i = 0;
		push_new_process(&g_vm->process, &g_vm->process_count, bot, total + i);
		while (i < bot->size)
		{
			g_map[total + i] = bot->exec[i];
			i++;
		}
		total += MEM_SIZE / g_vm->count_players;
		bot = bot->next;
	}
}

void		dispatcher_routes(void)
{
	if (g_vm->flag_client || g_vm->flag_server)
	{
		if (g_vm->flag_client && g_vm->flag_server)
			usage();
		else if ((g_vm->flag_client))
			client();
		else
			server();
	}
	else
	{
		fill_map();
		if (g_vm->flag_visual)
			visualize();
		else
			text_out();
	}
}

/*
** We go through an array of args and check whether
** argument is -dump, -n, -s (server), -c (client) or simply .cor file,
** and call corresponding functions.
*/

void		get_args(int argc, char **args)
{
	int	i;

	i = 0;
	while (++i < argc)
		parse_argument(argc, args, &i);
	(g_vm->count_players == 0 && !g_vm->flag_server) ? usage() : 0;
}

int			main(int ac, char **av)
{
	if (ac > 1)
	{
		init_vm();
		get_args(ac, av);
		sort_bot_list(&g_vm->bot, g_vm->count_players);
		dispatcher_routes();
	}
	else
		usage();
	return (0);
}
