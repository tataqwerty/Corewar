/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live_st_sti.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:06:18 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:06:19 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	live_bot_manage(t_bot *bot)
{
	(!g_vm->flag_visual && !g_vm->flag_dump)
		? ft_printf("A process shows that player %d (%s) is alive\n",
		bot->player_counter, bot->name) : 1;
	bot->lives_cur_period++;
	bot->last_live = g_vm->cur_cycle;
	g_vm->last_live_bot = bot;
}

void	ft_live(t_process *process)
{
	unsigned int	player_id;
	t_bot			*bot;

	process->live = 1;
	process->parent->bot_processes_lives++;
	player_id = get_arg((process->position + 1) % MEM_SIZE, 4);
	bot = g_vm->bot;
	while (bot)
	{
		if (player_id == bot->id)
		{
			live_bot_manage(bot);
			break ;
		}
		bot = bot->next;
	}
	if (g_vm->flag_visual && bot && player_id == bot->id)
		TURN_ON_LIVE;
	else if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	process->position = (process->position + 1 + 4) % MEM_SIZE;
	(g_vm->flag_visual) ? (TURN_ON_PROCESS) : 0;
}

void	ft_st(t_process *process)
{
	char			codage[4];
	short			position_arg2;
	unsigned char	result;

	decipher_codage(codage, COUNT_ARGS(OPCODE(2)), GET_CODAGE);
	if (check_valid_codage(OPCODE(2), codage) && ((result = get_arg(
		(process->position + 2) % MEM_SIZE, T_REG_SIZE)) > 0) && result < 17)
	{
		position_arg2 = get_arg((process->position + 3) % MEM_SIZE, ((codage[1]
			== IND_CODE) ? T_IND_SIZE : T_REG_SIZE));
		if (codage[1] == IND_CODE)
		{
			position_arg2 = position_arg2 % IDX_MOD;
			set_map_value(process, process->registries[result],
				(position_arg2 + process->position) % MEM_SIZE);
		}
		else if (position_arg2 > 0 && position_arg2 <= REG_NUMBER)
			process->registries[position_arg2] = process->registries[result];
	}
	change_process_position(OPCODE(2), codage, process);
}

int		ft_sti_check_args(unsigned int *uargs, short int *sargs, char *codage,
	t_process *process)
{
	int		i;
	char	offset;

	i = 0;
	offset = 2;
	while (i < 3)
	{
		if (codage[i] == REG_CODE)
		{
			uargs[i] = get_arg((process->position + offset) % MEM_SIZE,
				T_REG_SIZE);
			offset += T_REG_SIZE;
			if (uargs[i] < 1 || uargs[i] > 16)
				return (0);
		}
		else if (codage[i] == IND_CODE && (offset += T_IND_SIZE))
			uargs[i] = get_arg((process->position + (get_arg((process->position
			+ (offset - T_IND_SIZE)) % MEM_SIZE, T_IND_SIZE) % IDX_MOD))
			% MEM_SIZE, T_IND_READ);
		else if (codage[i] == DIR_CODE && (offset += T_DIR_SIZE))
			sargs[i] = get_arg((process->position
				+ (offset - T_DIR_SIZE)) % MEM_SIZE, T_DIR_SIZE);
		i++;
	}
	return (1);
}

/*
** "Значение T_REG (первый аргумент) записывается в ячейку, по адресу
** (текущая позиция PC плюс ((второй аргумент плюс третий аргумент) % IDX_MOD))
** - Если второй аргумент T_IND - то ясное дело, что вместо второго аргумента,
** в уровнение подставляются те 4 байта,
** которые мы берём из ячейки (T_IND % IDX_MOD)."
*/

void	ft_sti(t_process *process)
{
	char			codage[4];
	short int		sargs[3];
	unsigned int	uargs[3];
	int				ch_pos;

	decipher_codage(codage, COUNT_ARGS(11), GET_CODAGE);
	if (check_valid_codage(OPCODE(10), codage) && ft_sti_check_args(uargs,
		sargs, codage, process))
	{
		if (codage[1] == REG_CODE)
			ch_pos = process->registries[uargs[1]];
		else if (codage[1] == IND_CODE)
			ch_pos = uargs[1];
		else
			ch_pos = sargs[1];
		if (codage[2] == REG_CODE)
			ch_pos += process->registries[uargs[2]];
		else if (codage[2] == DIR_CODE)
			ch_pos += sargs[2];
		set_map_value(process, process->registries[uargs[0]],
			(process->position + (ch_pos % IDX_MOD)) % MEM_SIZE);
	}
	change_process_position(OPCODE(10), codage, process);
}
