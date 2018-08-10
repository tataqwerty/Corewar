/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 14:03:16 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/19 14:03:20 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void				check_magic_header(int fd)
{
	unsigned int	magic_header;

	if (read(fd, &magic_header, 4) != 4)
		ft_error(ERR_109);
	magic_header = reverse_bytes(magic_header, 4);
	if (magic_header != COREWAR_EXEC_MAGIC)
		ft_error(ERR_110);
}
