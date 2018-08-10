/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   staff2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/08 15:08:00 by opavliuk          #+#    #+#             */
/*   Updated: 2018/08/08 15:08:02 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char			get_arg_size(char opcode, char type)
{
	if (type == REG_CODE)
		return (T_REG_SIZE);
	else if (type == IND_CODE)
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
** Here I make bit-by-bit operation & for the last two bits in codage,
** as you may have guessed, with the number of 192 (128 + 64),
** and check whether these bits are on / off.
** After that I make a bitwise shift left on two bits.
*/

void			decipher_codage(char *arr, unsigned char n_args,
									unsigned char codage)
{
	int				i;
	unsigned char	tmp;

	i = 0;
	ft_bzero(arr, 4);
	while (codage && i < n_args)
	{
		tmp = codage & 192;
		(tmp == 192) ? (arr[i] = IND_CODE) : 0;
		(tmp == 128) ? (arr[i] = DIR_CODE) : 0;
		(tmp == 64) ? (arr[i] = REG_CODE) : 0;
		codage <<= 2;
		i++;
	}
}

/*
** This is the function that makes an array of types
** which must be presented after particular opcode,
** however such a function doesn't have at it's disposal
** such thing as codage.
**
** We loop through an array of arguments in the table,
** loop through of types in that argument,
** and check if this argument can be here,
** we save this type of argument.
*/

void			pseudo_codage(char *arr, char opcode)
{
	unsigned char	i;
	unsigned char	j;

	i = 0;
	ft_bzero(arr, 4);
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (ARG(opcode, i, j))
			{
				arr[i] = j + 1;
				break ;
			}
			j++;
		}
		i++;
	}
}

static t_bot	*bot_init(unsigned int id)
{
	t_bot			*new;

	if (((int)id >= 0) || ((int)id < -4))
		ft_error(ERR_114);
	new = (t_bot *)malloc(sizeof(t_bot));
	(!new) ? ft_error(ERR_101) : 0;
	new->player_counter = 0;
	ft_bzero(new->name, PROG_NAME_LENGTH + 1);
	ft_bzero(new->comment, COMMENT_LENGTH + 1);
	new->exec = NULL;
	new->id = id;
	new->size = 0;
	new->lives_cur_period = 0;
	new->lives_last_period = 0;
	new->last_live = 0;
	new->bot_processes_lives = 0;
	new->next = NULL;
	return (new);
}

t_bot			*push_new_bot(t_bot **head, unsigned int id)
{
	t_bot			*tmp;
	t_bot			*new;

	tmp = *head;
	while (tmp)
	{
		if (tmp->id == id)
			ft_error(ERR_113);
		else if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	new = bot_init(id);
	if (!*head)
		*head = new;
	else
		tmp->next = new;
	return (new);
}
