# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 12:18:21 by fredrika          #+#    #+#              #
#    Updated: 2019/12/03 15:07:14 by frlindh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME - COMPILATOR - FLAGS ************************************************** #
NAME			=	libft.a
GCC				=	gcc
FLAGS			=	-Wall -Wextra -Werror

# SRCS *********************************************************************** #
SRCS			=	ft_strcmp.c ft_puterr.c ft_split.c get_next_line.c \
					ft_atoi.c ft_atof.c ft_minmax.c

# OBJS *********************************************************************** #
OBJS			=	$(patsubst %.c, %.o, $(SRCS))

# RULES ********************************************************************** #

.PHONY: all clean fclean re

all: $(NAME) clean

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
