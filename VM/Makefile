# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysamchuk <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/08/09 20:14:03 by ysamchuk          #+#    #+#              #
#    Updated: 2018/08/09 20:14:05 by ysamchuk         ###   ########.fr        #
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

CC=		gcc

FLAGS=	-Wall -Wextra -Werror

NAME=	corewar

INCLD_DIR=		./include/
SRC_NAME_DIR=	./src/
SRC_NET_DIR=	./network_srcs/
SRC_VIS_DIR=	./visual_srcs/

HEADER=		./include/error.h\
			./include/corewar.h\
			./libft.h

SRC_VIS=	client_visualize.c\
			preparation.c\
			prepare_window.c\
			redraw.c\
			sidebar.c\
			sidebar_statistics.c\
			visual_staff.c\
			visualize.c

SRC_NET=	client.c\
			dispatcher_sockets.c\
			get_clients.c\
			get_clients_exec.c\
			get_data_from_server.c\
			get_game.c\
			network_staff.c\
			send_data_all_clients.c\
			server.c

SRC_NAME=	bot_parsing.c\
			check_exec.c\
			ft_add_sub.c\
			ft_and_or_xor.c\
			ft_fork_lfork.c\
			ft_ld_ldi_lld_lldi.c\
			ft_live_st_sti.c\
			get_server_info.c\
			main.c\
			parse_argument.c\
			process_function_ft_aff_zjmp.c\
			sort_bot_list.c\
			staff.c\
			staff2.c\
			step.c\
			text_output.c

SRC=$(addprefix $(SRC_NAME_DIR), $(SRC_NAME))\
	$(addprefix $(SRC_VIS_DIR), $(SRC_VIS))\
	$(addprefix $(SRC_NET_DIR), $(SRC_NET))

OBJ= $(SRC:%.c=%.o)

LIBFT_DIR= ../libft/
LIBFT= ../libft/libft.a

OK_STRING    =\#\#\#	$(GREEN)$(NAME)$(COLOR_OFF) is $(GREEN)READY!$(COLOR_OFF)	\#\#\#

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(LIBFT) $(OBJ) -I $(INCLD_DIR) -o $(NAME) -lncurses
	@printf "\n\n$(OK_STRING)\n\n"

%.o:%.c $(LIBFT) ./include/corewar.h ./include/error.h
	@$(CC) $(FLAGS) -c $< -I $(INCLD_DIR) -o $@ 
	@printf "$(CYAN)*$(COLOR_OFF)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJ)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@printf  "$(YELLOW)remove OBJ\n"

fclean:
	@printf "$(YELLOW)remove OBJ$(COLOR_OFF)\n"
	@$(MAKE) fclean -C ../libft
	@rm -f $(OBJ)
	@printf "$(RED)remove $(NAME)$(COLOR_OFF)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
