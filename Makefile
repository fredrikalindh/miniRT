# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 12:18:21 by fredrika          #+#    #+#              #
#    Updated: 2019/12/05 13:08:42 by frlindh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME - COMPILATOR - FLAGS ************************************************** #
NAME			=	minirt
GCC				=	gcc
FLAGS			=	-Wall -Wextra -Werror #-g3 -fsanitize=address
EXTRA			= 	-I ./minilibx -L ./minilibx -lmlx -framework OpenGL -framework AppKit
LIBFT			=	./libft/libft.a

# SRCS *********************************************************************** #
SRCS			=	main.c vectors.c color.c parse_objects.c parce.c rt.c \
					intersect.c vectors_math.c vectors_op.c \
					#ft_strcmp.c ft_puterr.c ft_split.c get_next_line.c \
					ft_atoi.c ft_atof.c ft_minmax.c

# OBJS *********************************************************************** #
OBJS			=	$(patsubst %.c, %.o, $(SRCS))

# RULES ********************************************************************** #

.PHONY: all clean fclean re

all: $(NAME) clean #remove this OBS !!!!!!!!!!!!

$(NAME): $(OBJS) $(LIBFT)
	$(GCC) $(FLAGS) $(EXTRA) -I ./libft $(LIBFT) $(OBJS) -o $(NAME)

$(LIBFT):
	cd libft && make

%.o: %.c
	$(GCC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all
