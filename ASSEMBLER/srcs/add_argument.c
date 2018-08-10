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

t_arg				*push_new_arg(t_arg **args)
{
	t_arg			*new;
	t_arg			*tmp;

	if (!(new = (t_arg *)malloc(sizeof(t_arg))))
		ft_error(ERR_MALLOC);
	new->str_value = NULL;
	new->num_value = 0;
	new->arg_size = 0;
	new->type = 0;
	new->flag = 0;
	new->next = NULL;
	tmp = *args;
	while (tmp && tmp->next)
		tmp = tmp->next;
	if (!tmp)
		*args = new;
	else
		tmp->next = new;
	return (new);
}

static	char		get_arg_size(char opcode, char type)
{
	if (type == T_REG)
		return (T_REG_SIZE);
	else if (type == T_IND)
		return (T_IND_SIZE);
	else
	{
		if (LABEL_SIZE(opcode) == 4)
			return (4);
		else
			return (T_DIR_SIZE);
	}
}

/*
** At the beginning we have ':'.
** 'return ((void*)my_strsub(str + 1, 0, ft_strlen(str) - 1))'
*/

void				*get_data(char type, char *str, char *flag)
{
	unsigned int	*num_val;

	if (type == T_REG)
	{
		*flag = UINT_VAL;
		num_val = (unsigned int *)malloc(sizeof(unsigned int));
		*num_val = ft_atoi(str + 1);
		return ((void*)num_val);
	}
	else
	{
		(*str == '%') ? str++ : 0;
		if (*str == ':')
		{
			*flag = STRING_VAL;
			return ((void*)my_strsub(str + 1, 0, ft_strlen(str) - 1));
		}
		else
		{
			*flag = UINT_VAL;
			num_val = (unsigned int *)malloc(sizeof(unsigned int));
			*num_val = ft_atoi(str);
			return ((void*)num_val);
		}
	}
}

/*
** We must return to this variable
** because it's just a pointer to a label
** which we cannot have on this stage.
** 'new->flag = 1'
*/

void				add_argument(t_command *command, char type,
					void *data, char flag)
{
	t_arg			*new;

	new = push_new_arg(&command->args);
	if (flag == STRING_VAL)
	{
		new->str_value = (char *)data;
		new->flag = 1;
	}
	else if (flag == UINT_VAL)
	{
		new->num_value = ((int *)data)[0];
		free(data);
	}
	new->type = type;
	new->arg_size = get_arg_size(command->opcode, type);
}
