# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 12:18:21 by fredrika          #+#    #+#              #
#    Updated: 2019/12/03 15:02:34 by frlindh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME - COMPILATOR - FLAGS ************************************************** #
NAME			=	minirt
GCC				=	gcc
FLAGS			=	-Wall -Wextra -Werror #-g3 -fsanitize=address
EXTRA			= 	-I ./minilibx -L ./minilibx -lmlx -framework OpenGL -framework AppKit
INCLUDES		=	./includes

# SRCS *********************************************************************** #
LIBSRCS			=	ft_strcmp.c ft_puterr.c ft_split.c get_next_line.c \
					ft_atoi.c ft_atof.c ft_minmax.c
NEWSRCS			=	main.c vectors.c color.c parse_objects.c parce.c
SRCS			=	$(addsuffix $(LIBSRCS), ./libft/) $(NEWSRCS)

# OBJS *********************************************************************** #
OBJS			=	$(patsubst %.c, %.o, $(SRCS))

# RULES ********************************************************************** #

.PHONY: all clean fclean re
include libft/lib.mk

all: $(NAME) clean

$(NAME): $(OBJS)
	$(GCC) $(FLAGS) $(EXTRA) $(OBJS) -o $(NAME) -I $(INCLUDES)

%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
