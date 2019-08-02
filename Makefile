# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/17 17:11:54 by cbrichau          #+#    #+#              #
#    Updated: 2019/07/28 18:39:34 by cbrichau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
FLAGS = -Wall -Wextra -Werror

H_DIR = includes
H_FILES = ft_printf.h
HDRS = $(addprefix $(H_DIR)/,$(H_FILES))

S_DIR = srcs
S_FILES = ft_printf.c ft_printf_extraction.c ft_printf_specifiers.c \
			ft_printf_conversion.c ft_printf_extraction2.c \
			ft_printf_conversion2.c ft_printf_flags_extras.c

O_DIR = objs
OBJS = $(addprefix $(O_DIR)/,$(S_FILES:.c=.o))

all: $(NAME)

$(NAME): $(O_DIR) $(OBJS)
	@echo "--- Create libft.a ---"
	@make all -C libft
	@echo "----------------------"
	@echo "Create $(NAME)"
	@cp libft/libft.a ./$(NAME)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(O_DIR):
	mkdir -p $(O_DIR)

$(O_DIR)/%.o: $(S_DIR)/%.c $(HDRS)
	@echo "Create $@"
	@$(CC) $(FLAGS) -I $(H_DIR) -o $@ -c $<

clean:
	@echo "Delete printf objects and directory"
	@rm -rf $(O_DIR)
	@make clean -C libft

fclean: clean
	@echo "Delete $(NAME)"
	@rm -f $(NAME)
	@echo "Delete libft.a"
	@rm -f libft.a libft/libft.a

re: fclean all

.PHONY: all clean fclean re
