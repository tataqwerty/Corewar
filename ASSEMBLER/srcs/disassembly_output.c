/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembly_output.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkiselev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 11:08:21 by tkiselev          #+#    #+#             */
/*   Updated: 2018/07/17 11:08:23 by tkiselev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			create_file(t_asm *asmb)
{
	int			end;
	char		*tmp;

	tmp = NULL;
	if (ft_strstr(asmb->file_name, ".cor"))
	{
		end = ft_strstr(asmb->file_name, ".cor") - asmb->file_name;
		tmp = my_strsub(asmb->file_name, 0, end);
		tmp = ft_strjoinfree(tmp, ".s", 1);
	}
	else
		tmp = ft_strdup(".s");
	ft_strdel(&asmb->file_name);
	asmb->file_name = tmp;
	asmb->new_fd = open(asmb->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (asmb->new_fd < 0)
		ft_error(ERR_NEW_FILE);
}

void			output_header(t_asm *asmb)
{
	ft_putstr_fd(NAME_CMD, asmb->new_fd);
	ft_putstr_fd(" \"", asmb->new_fd);
	if (ft_strlen(asmb->prog_name) > 0)
		ft_putstr_fd(asmb->prog_name, asmb->new_fd);
	ft_putstr_fd("\"\n", asmb->new_fd);
	ft_putstr_fd(COMMENT_CMD, asmb->new_fd);
	ft_putstr_fd(" \"", asmb->new_fd);
	if (ft_strlen(asmb->comment) > 0)
		ft_putstr_fd(asmb->comment, asmb->new_fd);
	ft_putstr_fd("\"\n\n", asmb->new_fd);
}

void			write_command(int fd, t_command *command)
{
	t_arg		*arg;

	arg = command->args;
	ft_putstr_fd("	", fd);
	ft_putstr_fd(NAME(command->opcode), fd);
	ft_putstr_fd("	", fd);
	while (arg)
	{
		if (arg->type == T_REG)
			write(fd, "r", 1);
		else if (arg->type == T_DIR)
			write(fd, "%", 1);
		ft_putnbr_fd(arg->num_value, fd);
		if (arg->next)
			write(fd, ", ", 2);
		arg = arg->next;
	}
	write(fd, "\n", 1);
}

void			output_commands(t_asm *asmb)
{
	t_command	*command;

	command = asmb->command;
	while (command)
	{
		write_command(asmb->new_fd, command);
		command = command->next;
	}
}

void			disassembly_output(t_asm *asmb)
{
	create_file(asmb);
	output_header(asmb);
	output_commands(asmb);
	ft_printf("Writing output program to %s\n", asmb->file_name);
	close(asmb->new_fd);
}
