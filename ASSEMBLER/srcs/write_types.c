/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_types.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 16:44:03 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/17 16:44:04 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			write_t_reg(t_command *command, int i, int fd)
{
	t_arg			*arg;
	unsigned char	buf;

	if (!ARG(command->opcode, i, T_REG))
		ft_error(ERR_NOT_COMPATIBLE_ARG);
	arg = push_new_arg(&command->args);
	if (read(fd, &buf, T_REG_SIZE) == 0)
		return (1);
	arg->num_value = (int)buf;
	arg->type = T_REG;
	return (0);
}

char			write_t_dir(t_command *command, int i, int fd)
{
	t_arg			*arg;
	unsigned int	buf;

	if (!ARG(command->opcode, i, T_DIR))
		ft_error(ERR_NOT_COMPATIBLE_ARG);
	arg = push_new_arg(&command->args);
	if (read(fd, &buf, LABEL_SIZE(command->opcode)) == 0)
		return (1);
	buf = reverse_bytes(buf, LABEL_SIZE(command->opcode));
	arg->num_value = (int)buf;
	arg->type = T_DIR;
	return (0);
}

char			write_t_ind(t_command *command, int i, int fd)
{
	t_arg			*arg;
	unsigned int	buf;

	if (!ARG(command->opcode, i, T_IND))
		ft_error(ERR_NOT_COMPATIBLE_ARG);
	arg = push_new_arg(&command->args);
	if (read(fd, &buf, T_IND_SIZE) == 0)
		return (1);
	buf = reverse_bytes(buf, T_IND_SIZE);
	arg->num_value = (int)buf;
	arg->type = T_IND;
	return (0);
}
