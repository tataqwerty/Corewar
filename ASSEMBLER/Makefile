# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: opavliuk <opavliuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/26 16:04:15 by opavliuk          #+#    #+#              #
#    Updated: 2018/06/08 13:37:57 by opavliuk         ###   ########.fr        #
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

CC=gcc 
CFLAGS=-Wall -Werror -Wextra
SRC=./srcs/add_argument.c \
	./srcs/compute_variables.c \
	./srcs/create_binary.c \
	./srcs/disassembly_output.c \
	./srcs/get_arguments.c \
	./srcs/get_commands.c \
	./srcs/get_header.c \
	./srcs/get_labels.c \
	./srcs/get_type.c \
	./srcs/read_binary.c \
	./srcs/show_bot.c \
	./srcs/staff.c \
	./srcs/staff2.c \
	./srcs/write_types.c \
	./srcs/main.c
	
INCLUDES=includes/
HEADER=includes/asm.h
OBJ=$(SRC:.c=.o)
LIB = ../libft/libft.a
LIB_HEADER=../libft/libft.h
NAME=asm

all: $(NAME)

%.o: %.c $(INCLUDES) $(LIB)
	@ $(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)
	@printf "$(CYAN)*$(COLOR_OFF)"

$(NAME): $(LIB) $(OBJ) $(HEADER) $(LIB_HEADER)
	@ $(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)
	@ printf "\n\n###	$(GREEN) asm $(COLOR_OFF) is $(GREEN)READY!$(COLOR_OFF) 	###\n\n"

$(LIB):
	@ make -C ../libft/

clean: 
	@ rm -f $(OBJ)
	@ make clean -C ../libft/
	@printf  "$(YELLOW)remove OBJ\n"

fclean: clean
	@ rm -f $(NAME)
	@ make fclean -C ../libft/
	@ printf "$(RED)remove $(NAME)$(COLOR_OFF)\n"

re: fclean all

.PHONY: all, clean, fclean, re
