/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fredrika <fredrika@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 09:54:38 by fredrika          #+#    #+#             */
/*   Updated: 2019/11/04 17:18:40 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_fullen(char *str, int flag)
{
	if (flag == 1)
	{
		while (str != NULL && *str != '\0')
		{
			if (*str == '\n')
				return (1);
			str++;
		}
		return (0);
	}
	else
		while (str != NULL && str[flag])
			flag++;
	return (flag);
}

static char	*ft_strcat(char *file, char *buf)
{
	char	*new;
	int		i;

	if (!(new = (char *)malloc(ft_fullen(file, 0) + ft_fullen(buf, 0) + 1)))
		return (NULL);
	i = 0;
	while (file != NULL && file[i])
	{
		new[i] = file[i];
		i++;
	}
	free(file);
	file = NULL;
	while (buf != NULL && *buf != '\0')
		new[i++] = *buf++;
	new[i] = '\0';
	return (new);
}

static char	*ft_cpyline(char **file, int fd, int i)
{
	int		j;
	char	*line;
	char	*temp;

	while (file[fd] && file[fd][i] != '\n' && file[fd][i] != '\0')
		i++;
	j = 0;
	if (!(line = (char *)malloc(i + 1)))
		return (NULL);
	i = -1;
	while (file[fd] && file[fd][++i] != '\n' && file[fd][i] != '\0')
		line[i] = file[fd][i];
	line[i] = '\0';
	if ((temp = NULL) == NULL && file[fd] && file[fd][i++] != '\0')
	{
		if (!(temp = (char *)malloc(ft_fullen(&file[fd][i], 0) + 1)))
			return (NULL);
		while (file[fd][i] != '\0')
			temp[j++] = file[fd][i++];
		temp[j] = '\0';
	}
	free(file[fd]);
	file[fd] = temp;
	return (line);
}

int			get_next_line(int fd, char **line)
{
	char		buf[BUFFER_SIZE + 1];
	int			ret;
	static char	*file[1024];

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1)
		return (-1);
	ret = -1;
	while (ft_fullen(file[fd], 1) == 0 && ret != 0)
	{
		if ((ret = read(fd, buf, BUFFER_SIZE)) == -1)
			return (-1);
		buf[ret] = '\0';
		file[fd] = ft_strcat(file[fd], buf);
	}
	*line = ft_cpyline(file, fd, 0);
	if (ret == 0)
		return (0);
	return (1);
}
