/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 16:39:55 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/16 16:39:57 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	void		get_codage(t_command *command)
{
	t_arg			*arg;
	unsigned char	n;
	char			len;

	if (!CODAGE(command->opcode))
		return ;
	n = 0;
	len = 4;
	arg = command->args;
	while (arg)
	{
		(n) ? (n <<= 2) : 0;
		(arg->type == T_REG) ? (n |= 1) : 0;
		(arg->type == T_DIR) ? (n |= 2) : 0;
		(arg->type == T_IND) ? (n |= 3) : 0;
		len--;
		arg = arg->next;
	}
	n <<= (len * 2);
	command->codage = n;
}

/*
** if (command->opcode) - because if opcode == 0,
** command doesn't exist.
*/

static	void		get_bytes(t_command *command)
{
	t_arg			*arg;

	if (command->opcode)
	{
		command->bytes++;
		arg = command->args;
		(CODAGE(command->opcode)) ? command->bytes++ : 0;
		while (arg)
		{
			command->bytes += arg->arg_size;
			arg = arg->next;
		}
	}
}

/*
** ft_error("Error") - if there is no such label.
*/

static	void		get_val_from_pointer(t_command *head,
						t_command *command, t_arg *arg)
{
	t_list			*label;

	while (head)
	{
		label = head->labels;
		while (label)
		{
			if (ft_strequ(label->content, arg->str_value))
			{
				arg->num_value = head->bb - command->bb;
				arg->flag = 0;
				return ;
			}
			label = label->next;
		}
		head = head->next;
	}
	ft_error(ERR_NO_SUCH_LABEL);
}

static	void		compute_tdirs(t_command *command)
{
	t_command		*tmp;
	t_arg			*arg;

	tmp = command;
	while (tmp)
	{
		arg = tmp->args;
		while (arg)
		{
			if (arg->flag)
				get_val_from_pointer(command, tmp, arg);
			arg = arg->next;
		}
		tmp = tmp->next;
	}
}

unsigned int		compute_variables(t_command *command)
{
	t_command		*tmp;

	tmp = command;
	while (command)
	{
		get_codage(command);
		get_bytes(command);
		if (command->next)
		{
			command->next->bb = command->bb + command->bytes;
			command = command->next;
		}
		else
			break ;
	}
	compute_tdirs(tmp);
	return (command->bb + command->bytes);
}
