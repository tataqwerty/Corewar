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

/*
** We pass flag just in order to determine if this argument is INT or CHAR *.
** 'add_argument(command, type, get_data(type, arr[i], &flag), flag)'
*/

static	void	foreach_arg(char **arr, t_command *command)
{
	int			i;
	char		type;
	char		flag;

	i = 0;
	while (arr[i])
	{
		flag = 0;
		type = get_type(arr[i]);
		if (type == UNDEFINED_TYPE)
			ft_error(ERR_UNDEFINED_ARG);
		add_argument(command, type, get_data(type, arr[i], &flag), flag);
		i++;
	}
}

static	void	check_arguments(t_command *command)
{
	t_arg		*arg;
	int			len;

	len = 0;
	arg = command->args;
	while (arg)
	{
		(len > 3) ? ft_error(ERR_TOO_MUCH_ARGS) : 0;
		if (!ARG(command->opcode, len, arg->type))
			ft_error(ERR_NOT_COMPATIBLE_ARG);
		len++;
		arg = arg->next;
	}
	(COUNT_ARGS(command->opcode) != len) ? ft_error(ERR_COUNT_ARGS) : 0;
}

/*
** k - it is a temporary variable that represents
** the beginning of the next argument.
** q - is is a temporary variable that represents
** quantity of ',' between two arguments.
** i - is is a temporary variable that represents
** quantity of arguments.
*/

static	void	skip_args(char *s, char **arr, int *j)
{
	int			i;
	int			k;
	int			q;

	i = 0;
	k = 0;
	while (arr[i])
	{
		*j = ft_strstr(s + *j, arr[i]) - s + ft_strlen(arr[i]);
		if (arr[i + 1])
		{
			k = ft_strstr(s + *j, arr[i + 1]) - s;
			q = 0;
			while (*j < k)
			{
				(s[*j] == SEPARATOR_CHAR) ? q++ : 0;
				(*j)++;
			}
			(q != 1) ? ft_error(ERR_TOO_MUCH_SEPARATORS) : 0;
		}
		i++;
	}
}

static	void	array_map(char **arr, void (*f)(char **))
{
	int			i;

	i = 0;
	while (arr[i])
	{
		(*f)(&arr[i]);
		i++;
	}
}

void			get_arguments(t_asm *asmb, t_command *new, int *j)
{
	char		**arr;

	if (!(arr = ft_strsplit(asmb->line + *j, SEPARATOR_CHAR)))
		ft_error(ERR_MALLOC);
	array_map(arr, ft_strtrim);
	foreach_arg(arr, new);
	skip_args(asmb->line, arr, j);
	array_map(arr, ft_strdel);
	free(arr);
	check_arguments(new);
}
