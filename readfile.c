/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:12:32 by frlindh           #+#    #+#             */
/*   Updated: 2019/11/13 11:09:12 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int		check_rt(char *f)
{
	int		i;

	i = -1;
	while (f && f[++i])
	{
		if (f[i] == '.' && f[i + 1] != 'r' && f[i + 2] != 't' && f[i + 3] != 't')
			return (-1);
	}
	return (i);
}

void	init_info(int fd, int argc, t_rt *rt)
{
	char	*line;
	char	**split; //split with whitespace and ','

	if (argc == 3)
		rt->save = 1;
	while (get_next_line(&line) > 0)
	{
		if (line && *line)
			split = ft_split(line);
		ft_assign(split, rt); // so in here depending on split[0] the struct will be filled
		free(line);
		free(split);
		split = NULL;
	}
}

int		ft_getinfo(int argc, char const *argv[], t_rt *rt)
{
	int		fd;

	if (argc == 0)
		ft_puterr("Error: scene description file is missing");
	else if (argc > 3)
		ft_puterr("Error: unvalid amount of argument");
	else if (argc == 3 && argv[2] != "–-save")
		ft_puterr("Error: unvalid arguments");
	else if (check_rt(argv[1]) < 1)
		ft_puterr("Error: .rt file is missing");
	else if (fd = open(argv[1], O_RDONLY) == -1)
		ft_puterr("Error opening file");
	else
	{
		init_info(fd, argc, rt);
		return (1);
	}
	return (-1);
}

int		main(int argc, char const *argv[])
{
	t_rt	rt;

	if (ft_getinfo(argc[1], t_rt &rt) == -1)
		return (-1);

	return (0);
}
