/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 13:21:59 by tkuhar            #+#    #+#             */
/*   Updated: 2018/08/01 13:21:59 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_header(void)
{
	t_bot			*cur_bot;

	ft_printf("Introducing contestants...\n");
	cur_bot = g_vm->bot;
	while (cur_bot)
	{
		ft_printf("* Player %u, weighing %u bytes, \"%s\" (\"%s\") !\n",
			(-1) * (int)cur_bot->id, cur_bot->size,
			cur_bot->name, cur_bot->comment);
		cur_bot = cur_bot->next;
	}
}

void		dump_print(void)
{
	int		i;

	i = -1;
	while (++i < MEM_SIZE)
	{
		if (!(i % 64) && i)
			ft_printf("\n");
		if (!(i % 64))
			ft_printf("0x%04x :", i);
		ft_printf(" %02x", g_map[i]);
	}
	ft_printf("\n");
}

void		print_winer(void)
{
	ft_printf("Player %i (%s) won\n", (-1) * (int)g_vm->winner->id,
		g_vm->winner->name);
}

void		text_out(void)
{
	print_header();
	while (!g_vm->winner && !(g_vm->flag_dump &&
			g_vm->cur_cycle == g_vm->dump_cycles))
		step();
	if (g_vm->flag_dump && g_vm->cur_cycle == g_vm->dump_cycles)
		dump_print();
	else if (g_vm->winner)
		print_winer();
}
