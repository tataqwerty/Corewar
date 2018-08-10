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

void	ft_error(char *str)
{
	ft_printf("%s\n", str);
	exit(0);
}

void	skip_shit(char *str, int *j, char *symbols)
{
	while (str[*j] && ft_strchr(symbols, str[*j]))
		(*j)++;
}

void	comment_delete(char *str)
{
	while (*str && (*str != ';' && *str != '#'))
		str++;
	if (*str != '\0')
		ft_bzero(str, ft_strlen(str));
}

char	check_line(char *s)
{
	if (s)
	{
		while (*s && (*s == ' ' || *s == '\t'))
			s++;
		if (*s == '\0')
			return (1);
	}
	return (0);
}

int		index_of(char *needle, int len)
{
	int i;

	i = 0;
	while (i < MAX_TABLE)
	{
		if (ft_strnequ(NAME(i + 1), needle, len))
			return (i);
		i++;
	}
	return (-1);
}
