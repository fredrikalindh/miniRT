/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:53:59 by frlindh           #+#    #+#             */
/*   Updated: 2019/12/03 15:07:57 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

// library functions ?
int			get_next_line(int fd, char **line);
double		ft_atof(char *str);
int			ft_atoi(char *str);
void		ft_puterr(char *str);
int			ft_strcmp(char *s1, char *s2);
char		**ft_split(char *str);
int			ft_min(int a, int b);
int			ft_max(int a, int b);
void		ft_putnbr_fd(int n, int fd);

#endif
