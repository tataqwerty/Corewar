/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bot_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:08:38 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:08:40 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** This function gives to every bot unique player counter from 1 to 4,
** player counter corresponds to certain color.
*/

static void		give_player_counter_to_bots(t_bot *bot)
{
	unsigned char	player_counter;

	player_counter = 1;
	while (bot)
	{
		bot->player_counter = player_counter;
		player_counter++;
		g_vm->last_live_bot = bot;
		bot = bot->next;
	}
}

static void		bot_swap(t_bot **head, t_bot *prev, t_bot **cur, t_bot **next)
{
	t_bot		*tmp;

	(*cur)->next = (*next)->next;
	(*next)->next = *cur;
	if (prev)
		prev->next = *next;
	else
		*head = *next;
	tmp = *next;
	*next = *cur;
	*cur = tmp;
}

void			sort_bot_list(t_bot **head, unsigned char count_players)
{
	unsigned char	i;
	t_bot			*prev;
	t_bot			*cur;
	t_bot			*next;

	i = 0;
	while (++i < count_players)
	{
		prev = NULL;
		cur = *head;
		next = cur->next;
		while (next)
		{
			if (cur->id < next->id)
				bot_swap(head, prev, &cur, &next);
			prev = cur;
			cur = next;
			next = next->next;
		}
	}
	give_player_counter_to_bots(g_vm->bot);
}
