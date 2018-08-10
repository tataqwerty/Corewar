/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/21 17:36:20 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/21 17:36:21 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		output_chars(unsigned char *s, unsigned char len,
			unsigned char spaces)
{
	unsigned char	i;

	while (spaces-- > 0)
		write(1, " ", 1);
	i = 0;
	while (i < len)
	{
		if (s[i] > 32 && s[i] < 127)
			write(1, &s[i], 1);
		else
			write(1, ".", 1);
		i++;
	}
	write(1, "\n", 1);
}

static void		print_hex(unsigned char c)
{
	char		*base;

	base = "0123456789abcdef";
	write(1, &base[c / 16], 1);
	write(1, &base[c % 16], 1);
}

void			print_memory(const void *addr, size_t size)
{
	unsigned char	*tab;
	unsigned char	i;
	unsigned char	spaces;

	tab = (unsigned char *)addr;
	while (size != 0 && tab)
	{
		i = 0;
		spaces = 40;
		while (i < 16 && size != 0)
		{
			print_hex(tab[i]);
			i++;
			spaces -= 2;
			size--;
			if (i % 2 == 0)
			{
				write(1, " ", 1);
				spaces--;
			}
		}
		output_chars(tab, i, spaces);
		tab += i;
	}
}
