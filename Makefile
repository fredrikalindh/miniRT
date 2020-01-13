# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/15 12:18:21 by fredrika          #+#    #+#              #
#    Updated: 2020/01/13 15:33:29 by frlindh          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# NAME - COMPILATOR - FLAGS ************************************************** #
NAME			=	minirt
GCC				=	gcc
FLAGS			=	-Wall -Wextra -Werror #-g3 -fsanitize=address
EXTRA			= 	-I ./minilibx -L ./minilibx -lmlx -framework OpenGL -framework AppKit
# LIBFT			=	./my_lib/libft.a
IDIR			=	-I ./includes

# SRCS *********************************************************************** #
SRCS			=	main.c vectors.c color.c parse_objects.c parce.c rt.c \
					intersect.c vectors_math.c vectors_op.c trans.c ranges.c \
					initrt.c image.c cyl.c deal.c checked.c lights.c\
					ft_atof.c \
					ft_atoi.c \
					ft_minmax.c \
					ft_puterr.c \
					ft_puterr2.c \
					ft_putnbr_fd.c \
					ft_putchar_fd.c \
					ft_split.c \
					ft_strcmp.c \
					ft_strlen.c \
					get_next_line.c \
					is_digit.c
SRCS_BONUS		=	main.c vectors.c color.c parse_objects.c parce.c rt_bonus.c \
					intersect.c vectors_math.c vectors_op.c trans.c ranges.c \
					initrt.c image.c cyl.c deal.c checked.c lights.c\
					ft_atof.c \
					ft_atoi.c \
					ft_minmax.c \
					ft_puterr.c \
					ft_puterr2.c \
					ft_putnbr_fd.c \
					ft_putchar_fd.c \
					ft_split.c \
					ft_strcmp.c \
					ft_strlen.c \
					get_next_line.c \
					is_digit.c

# OBJS *********************************************************************** #
OBJS			=	$(patsubst %.c, %.o, $(SRCS))
OBJS_BONUS		=	$(patsubst %.c, %.o, $(SRCS_BONUS))

# RULES ********************************************************************** #

.PHONY: all clean fclean re

all: $(NAME) #clean #remove this OBS !!!!!!!!!!!!

$(NAME): $(OBJS) ./includes/*.h
	$(GCC) $(FLAGS) $(EXTRA) $(OBJS) -o $(NAME)

bonus: $(OBJS_BONUS) ./includes/*.h
	$(GCC) $(FLAGS) $(EXTRA) $(OBJS_BONUS) -o $(NAME) -lpthread

%.o: %.c
	$(GCC) $(FLAGS) $(IDIR) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
