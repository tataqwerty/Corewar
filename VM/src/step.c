/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkuhar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 14:05:59 by tkuhar            #+#    #+#             */
/*   Updated: 2018/07/30 17:45:55 by tkuhar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		reset_cur_period(void)
{
	t_bot			*cur_bot;
	unsigned int	max;

	max = 0;
	cur_bot = g_vm->bot;
	while (cur_bot)
	{
		max = max + cur_bot->bot_processes_lives;
		cur_bot->lives_last_period = cur_bot->lives_cur_period;
		cur_bot->lives_cur_period = 0;
		cur_bot->bot_processes_lives = 0;
		cur_bot = cur_bot->next;
	}
	(max < NBR_LIVE) ? max = 0 : 0;
	return (max);
}

static void		time_to_die(void)
{
	t_process	*cur_p;
	t_process	*prev;

	prev = 0;
	cur_p = g_vm->process;
	while (cur_p)
		if (!(cur_p->live))
		{
			prev ? prev->next = cur_p->next : 0;
			!prev ? g_vm->process = cur_p->next : 0;
			(g_vm->flag_visual) ? (g_pixels[cur_p->position]->color =
				g_pixels[cur_p->position]->color % 10) : 1;
			free(cur_p);
			g_vm->process_count--;
			cur_p = prev ? prev->next : g_vm->process;
		}
		else
		{
			cur_p->live = 0;
			prev = cur_p;
			cur_p = cur_p->next;
		}
}

static void		do_proceses(t_process *process)
{
	while (process)
	{
		if (!process->opcode && (!g_map[process->position]
			|| g_map[process->position] > 16))
		{
			(g_vm->flag_visual) ? SET_PIXEL_COLOR : 1;
			process->position = ((process->position) + 1) % MEM_SIZE;
			(g_vm->flag_visual) ? TURN_ON_PROCESS : 1;
		}
		else if (!process->opcode)
		{
			process->opcode = g_map[process->position];
			process->cycles_to_perform = PREFORM(process->opcode) - 2;
		}
		else if (process->cycles_to_perform > 0)
			process->cycles_to_perform--;
		else if (!process->cycles_to_perform)
		{
			g_func[process->opcode - 1](process);
			process->opcode = 0;
		}
		if (g_vm->flag_visual && g_pixels[process->position]->color < 10)
			TURN_ON_PROCESS;
		process = process->next;
	}
}

int				step(void)
{
	g_vm->cur_cycle++;
	do_proceses(g_vm->process);
	if (g_vm->cur_cycle == g_vm->future_die)
	{
		g_vm->last_change_cycle_to_die++;
		if (reset_cur_period() || g_vm->last_change_cycle_to_die >= MAX_CHECKS)
		{
			g_vm->cycle_to_die -= CYCLE_DELTA;
			g_vm->last_change_cycle_to_die = 0;
		}
		g_vm->future_die = g_vm->cur_cycle + g_vm->cycle_to_die;
		time_to_die();
	}
	(!g_vm->process || ((int)g_vm->cycle_to_die <= 0))
		? g_vm->winner = g_vm->last_live_bot : 0;
	return (0);
}
