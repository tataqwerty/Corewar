/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_lfork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:05:24 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:05:28 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	copy_new_process(t_process **head, t_process *process_old,
		unsigned int position)
{
	t_process	*process;
	int			i;

	i = 1;
	process = (t_process *)malloc(sizeof(t_process));
	(!process) ? ft_error(ERR_101) : 0;
	while (i <= REG_NUMBER)
	{
		process->registries[i] = process_old->registries[i];
		i++;
	}
	process->parent = process_old->parent;
	process->position = position;
	(g_vm->flag_visual) ? TURN_ON_PROCESS : 1;
	process->carry = process_old->carry;
	process->live = process_old->live;
	process->opcode = 0;
	process->codage = process_old->codage;
	process->cycles_to_perform = 0;
	process->next = NULL;
	if (*head)
		process->next = *head;
	*head = process;
	(g_vm->process_count)++;
}

void	ft_fork(t_process *process)
{
	short new_position;

	new_position = ((short)(get_arg((process->position + 1)
		% MEM_SIZE, T_DIR_SIZE)) % IDX_MOD);
	copy_new_process(&(g_vm->process), process,
		((new_position + process->position) % MEM_SIZE));
	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	process->position = (process->position + T_DIR_SIZE + 1) % MEM_SIZE;
	if (g_vm->flag_visual)
		TURN_ON_PROCESS;
}

void	ft_lfork(t_process *process)
{
	short new_position;

	new_position = (short)get_arg((process->position + 1) % MEM_SIZE,
		T_DIR_SIZE);
	copy_new_process(&(g_vm->process), process,
		((new_position + process->position) % MEM_SIZE));
	if (g_vm->flag_visual)
		SET_PIXEL_COLOR;
	process->position = (process->position + T_DIR_SIZE + 1) % MEM_SIZE;
	if (g_vm->flag_visual)
		TURN_ON_PROCESS;
}
