/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:05:52 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:05:54 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	ft_add(t_process *process)
{
	int				i;
	char			codage[4];
	unsigned char	args[3];

	i = 0;
	decipher_codage(codage, COUNT_ARGS(OPCODE(3)), GET_CODAGE);
	if (check_valid_codage(OPCODE(3), codage))
	{
		while (i < 3)
		{
			args[i] = get_arg((process->position + 1 + (i + T_REG_SIZE))
				% MEM_SIZE, T_REG_SIZE);
			if (!(args[i] > 0 && args[i] < 17))
				break ;
			i++;
		}
		if (i == 3)
		{
			process->registries[args[2]] = process->registries[args[0]]
			+ process->registries[args[1]];
			process->carry = (process->registries[args[2]]) ? 0 : 1;
		}
	}
	change_process_position(OPCODE(3), codage, process);
}

void	ft_sub(t_process *process)
{
	int				i;
	char			codage[4];
	unsigned char	args[3];

	i = 0;
	decipher_codage(codage, COUNT_ARGS(OPCODE(4)), GET_CODAGE);
	if (check_valid_codage(OPCODE(4), codage))
	{
		while (i < 3)
		{
			args[i] = get_arg((process->position + 1 + (i + T_REG_SIZE))
				% MEM_SIZE, T_REG_SIZE);
			if (!(args[i] > 0 && args[i] < 17))
				break ;
			i++;
		}
		if (i == 3)
		{
			process->registries[args[2]] = process->registries[args[0]]
			- process->registries[args[1]];
			process->carry = (process->registries[args[2]] != 0) ? 0 : 1;
		}
	}
	change_process_position(OPCODE(4), codage, process);
}
