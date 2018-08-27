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

static	char	is_treg(char *str)
{
	int			tmp;

	if (*str == 'r')
	{
		str++;
		if (!ft_is_uint(str) || *str == '-' || *str == '+')
			return (0);
		tmp = ft_atoi(str);
		if (tmp >= 0 && tmp <= REG_NUMBER)
			return (1);
	}
	return (0);
}

static	char	is_tdir(char *str)
{
	if (*str == '%')
	{
		str++;
		if (*str == ':')
		{
			str++;
			if (!ft_strchr(str, ':'))
				return (1);
		}
		else if (*str)
		{
			(*str == '-') ? str++ : 0;
			while (ft_isdigit(*str))
				str++;
			if (*str == '\0')
				return (1);
		}
	}
	return (0);
}

static	char	is_tind(char *str)
{
	if (*str == ':')
	{
		str++;
		if (!ft_strchr(str, ':'))
			return (1);
	}
	else if (*str)
	{
		(*str == '-') ? str++ : 0;
		while (ft_isdigit(*str))
			str++;
		if (*str == '\0')
			return (1);
	}
	return (0);
}

char			get_type(char *str)
{
	if (is_treg(str))
		return (T_REG);
	else if (is_tdir(str))
		return (T_DIR);
	else if (is_tind(str))
		return (T_IND);
	return (UNDEFINED_TYPE);
}
