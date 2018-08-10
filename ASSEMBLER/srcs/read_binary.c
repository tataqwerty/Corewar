/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_binary.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opavliuk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 10:37:29 by opavliuk          #+#    #+#             */
/*   Updated: 2018/07/17 10:37:30 by opavliuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		read_info(t_asm *asmb)
{
	char	null[4];

	if (read(asmb->fd, &asmb->magic, 4) == 0)
		ft_error(ERR_NOT_ENOUGH_DATA);
	asmb->magic = reverse_bytes(asmb->magic, 4);
	if (asmb->magic != COREWAR_EXEC_MAGIC)
		ft_error(ERR_HEADER);
	if (read(asmb->fd, asmb->prog_name, PROG_NAME_LENGTH) == 0)
		ft_error(ERR_NOT_ENOUGH_DATA);
	if (read(asmb->fd, null, 4) == 0)
		ft_error(ERR_NOT_ENOUGH_DATA);
	if (read(asmb->fd, &asmb->prog_size, 4) == 0)
		ft_error(ERR_NOT_ENOUGH_DATA);
	asmb->prog_size = reverse_bytes(asmb->prog_size, 4);
	if (read(asmb->fd, asmb->comment, COMMENT_LENGTH) == 0)
		ft_error(ERR_NOT_ENOUGH_DATA);
	if (read(asmb->fd, null, 4) == 0)
		ft_error(ERR_NOT_ENOUGH_DATA);
}

static char		check_codage(t_command *command, int fd)
{
	int		i;

	i = 0;
	while (i < COUNT_ARGS(command->opcode))
	{
		if (!(command->codage & 128) && (command->codage & 64))
			if (write_t_reg(command, i, fd))
				return (1);
		if ((command->codage & 128) && !(command->codage & 64))
			if (write_t_dir(command, i, fd))
				return (1);
		if ((command->codage & 128) && (command->codage & 64))
			if (write_t_ind(command, i, fd))
				return (1);
		i++;
		command->codage <<= 2;
	}
	return (0);
}

static void		read_executable(t_asm *asmb)
{
	t_command		*command;
	unsigned char	buf[1];

	while (read(asmb->fd, buf, 1) != 0)
	{
		command = push_new_command(&asmb->command);
		command->opcode = buf[0];
		if (CODAGE(command->opcode) && read(asmb->fd, buf, 1) == 0)
			break ;
		else if (CODAGE(command->opcode))
			command->codage = buf[0];
		if (CODAGE(command->opcode) && check_codage(command, asmb->fd))
			break ;
		else if (!CODAGE(command->opcode))
		{
			if (write_t_dir(command, 0, asmb->fd))
				break ;
		}
	}
}

void			read_binary(t_asm *asmb)
{
	read_info(asmb);
	read_executable(asmb);
	disassembly_output(asmb);
}
