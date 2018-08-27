# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysamchuk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/09 20:13:30 by ysamchuk          #+#    #+#              #
#    Updated: 2018/08/09 20:13:37 by ysamchuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOR_OFF=\033[0m#			# Text Reset
BLACK	=\033[0;30m#		# Black
RED		=\033[0;31m#		# Red
GREEN	=\033[0;32m#		# Green
YELLOW	=\033[0;33m#		# Yellow
BLUE	=\033[0;34m#		# Blue
PURPLE	=\033[0;35m#		# Purple
CYAN	=\033[0;36m#		# Cyan
WHITE	=\033[0;37m#		# White

OK_STRING    =\#\#\#	 $(NAME) created		\#\#\#


VM_D=./VM/
ASM_D=./ASSEMBLER/


VM=		corewar
ASM=	asm

all: virtual assemb

virtual:
	@$(MAKE) -C $(VM_D)
	@cp $(VM_D)$(VM) $(VM)

assemb:
	@$(MAKE) -C $(ASM_D)
	@cp $(ASM_D)$(ASM) $(ASM)

clean:
	@$(MAKE) clean -C $(VM_D)
	@$(MAKE) clean -C $(ASM_D)

fclean:
	@$(MAKE) fclean -C $(VM_D)
	@$(MAKE) fclean -C $(ASM_D)
	@rm -f $(VM)
	@rm -f $(ASM)

re: fclean all

.PHONY: all, clean, fclean, re
