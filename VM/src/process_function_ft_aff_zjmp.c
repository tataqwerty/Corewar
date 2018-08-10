/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_function_ft_aff_zjmp.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:06:52 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:06:53 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		check_valid_codage(char opcode, char *codage)
{
	int		input_arg;
	int		possible_arg;
	int		it_was;

	input_arg = 0;
	while (input_arg < COUNT_ARGS(opcode))
	{
		possible_arg = 0;
		it_was = 0;
		while (possible_arg < 3)
		{
			if (ARG(opcode, input_arg, possible_arg)
				&& codage[input_arg] == possible_arg + 1)
				it_was = 1;
			possible_arg++;
		}
		if (!it_was)
			return (0);
		input_arg++;
	}
	return (1);
}

void	change_process_position(char opcode, char *codage, t_process *process)
{
	char	offset;
	int		i;

	offset = 0;
	i = 0;
	while (i < 3)
	{
		(codage[i] == IND_CODE) ? (offset += T_IND_SIZE) : 0;
		(codage[i] == REG_CODE) ? (offset += T_REG_SIZE) : 0;
		(codage[i] == DIR_CODE) ? (offset += LABEL_SIZE(opcode)) : 0;
		i++;
	}
	(g_vm->flag_visual) ? (g_pixels[process->position]->color =
				g_pixels[process->position]->color % 10) : 0;
	process->position = ((process->position) + offset + 1 + CODAGE(opcode))
		% MEM_SIZE;
	(g_vm->flag_visual) ? (g_pixels[process->position]->color =
				(g_pixels[process->position]->color % 10) + 20) : 0;
}

void	ft_zjmp(t_process *process)
{
	short	new_position;

	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	if (process->carry)
	{
		new_position = (short)get_arg((process->position + 1) % MEM_SIZE,
			T_DIR_SIZE) % IDX_MOD;
		process->position = (process->position + new_position) % MEM_SIZE;
	}
	else
		process->position = (process->position + 1 + T_DIR_SIZE) % MEM_SIZE;
	if (g_vm->flag_visual)
		TURN_ON_PROCESS;
}

void	ft_aff(t_process *process)
{
	char			codage[4];
	unsigned char	reg_num;

	decipher_codage(codage, COUNT_ARGS(OPCODE(15)), GET_CODAGE);
	if (codage[0] == REG_CODE)
	{
		reg_num = (unsigned char)get_arg((process->position + 2)
			% MEM_SIZE, T_REG_SIZE);
		if (reg_num > 0 && reg_num < 17 && !g_vm->flag_visual
			&& !g_vm->flag_dump)
			ft_printf("AFF: %c\n", process->registries[reg_num] % 256);
	}
	change_process_position(OPCODE(15), codage, process);
}

/*
** set_map_value() - print 4 bytes on the g_map and set appropriate
** values in g_pixels array
*/

void	set_map_value(t_process *process, unsigned int val,
		unsigned int new_pstn)
{
	int	j;

	j = 0;
	while (j < 4)
	{
		g_map[(new_pstn + j) % MEM_SIZE] = ((unsigned char *)&val)[3 - j];
		if (g_vm->flag_visual)
		{
			g_pixels[(new_pstn + j) % MEM_SIZE]->counter = 50;
			if (g_pixels[(new_pstn + j) % MEM_SIZE]->color / 10 == 2)
				g_pixels[(new_pstn + j) %
					MEM_SIZE]->color = process->parent->player_counter + 20;
			else
				g_pixels[(new_pstn + j) %
					MEM_SIZE]->color = process->parent->player_counter;
		}
		j++;
	}
}
