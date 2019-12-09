# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 12:18:21 by fredrika          #+#    #+#              #
#    Updated: 2019/12/09 13:48:54 by frlindh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME - COMPILATOR - FLAGS ************************************************** #
NAME			=	libft.a
GCC				=	gcc
FLAGS			=	-Wall -Wextra -Werror
IDIR			=	-I ../includes/

# SRCS *********************************************************************** #
SRCSLIST		=	ft_atof.c \
					ft_atoi.c \
					ft_minmax.c \
					ft_printf.c \
					ft_puterr.c \
					ft_putnbr_fd.c \
					ft_putchar_fd.c \
					ft_split.c \
					ft_strcmp.c \
					ft_strlen.c \
					ft_strnlen.c \
					get_next_line.c \
					skip_atoi.c \
					to_c.c \
					to_n.c \
					to_nbr.c \
					to_s.c

SRCS			=	$(addprefix srcs/, $(SRCSLIST))

# OBJS *********************************************************************** #
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

# RULES ********************************************************************** #
.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(GCC) $(FLAGS) $(IDIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
