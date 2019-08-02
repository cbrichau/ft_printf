# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cbrichau <cbrichau@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/24 14:51:12 by cbrichau          #+#    #+#              #
#    Updated: 2019/07/28 18:38:35 by cbrichau         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
FLAGS = -Wall -Wextra -Werror

H_DIR = includes
H_FILES = libft.h libft_extra.h
HDRS = $(addprefix $(H_DIR)/,$(H_FILES))

S_DIR = srcs
S_FILES = ft_atoi.c ft_memset.c ft_strcmp.c ft_strjoin.c ft_bzero.c \
		  ft_putstr.c ft_strcpy.c ft_strlen.c ft_isdigit.c ft_putstr_fd.c \
		  ft_strdel.c ft_strncpy.c ft_itoa.c ft_strcat.c ft_strdup.c ft_strnew.c
SE_DIR = srcs-extra
SE_FILES = ft_memset_start.c ft_strcat_reversed.c ft_itoa_big.c \
			ft_itoa_base.c ft_dtoa.c ft_dtoa_in_range.c ft_decimal_to_binary.c \
			ft_binary_to_base_8_16.c ft_c_in_str.c ft_convert_case.c

O_DIR = objs
OBJS = $(addprefix $(O_DIR)/,$(S_FILES:.c=.o)) \
		$(addprefix $(O_DIR)/,$(SE_FILES:.c=.o))

all: $(NAME)

$(NAME): $(O_DIR) $(OBJS)
	@echo "Create $(NAME)"
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(O_DIR):
	mkdir -p $(O_DIR)

$(O_DIR)/%.o: $(S_DIR)/%.c $(HDRS)
	@echo "Create $@"
	@$(CC) $(FLAGS) -I $(H_DIR) -o $@ -c $<

$(O_DIR)/%.o: $(SE_DIR)/%.c $(HDRS)
	@echo "Create $@"
	@$(CC) $(FLAGS) -I $(H_DIR) -o $@ -c $<

clean:
	@echo "Delete libft objects and directory"
	@rm -rf $(O_DIR)

fclean: clean
	@echo "Delete $(NAME)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
