/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:11:48 by frlindh           #+#    #+#             */
/*   Updated: 2020/01/20 19:35:35 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

static void	fill_split(char **split, char *str)
{
	int		i;
	int		j;
	int		a;

	i = 0;
	a = 0;
	while (str[i])
	{
		while ((str[i] == ' ' || str[i] == '	' || str[i] == ',') && str[i])
			i++;
		j = 0;
		while (str[i + j] != ' ' && str[i + j] != '	' && str[i + j] != ',' &&
		str[i + j])
			j++;
		if (!(split[a] = (char *)malloc(sizeof(char) * (j + 2))))
			return ;
		j = 0;
		while (str[i] != ' ' && str[i] != '	' && str[i] != ',' && str[i])
			split[a][j++] = str[i++];
		split[a][j] = '\0';
		a++;
	}
	if (str[i - 1] == ' ' || str[i - 1] == '	' || str[i - 1] == ',')
		a--;
	split[a] = NULL;
}

char		**ft_split(char *str)
{
	int		wc;
	int		i;
	char	**split;

	wc = 0;
	split = NULL;
	if ((i = 0) == 0 && (str == NULL || *str == '\0' || *str == '#'))
	{
		free(str);
		return (NULL);
	}
	while (str[i])
	{
		while ((str[i] == ' ' || str[i] == '	' || str[i] == ',') && str[i])
			i++;
		if (str[i])
			wc++;
		while (str[i] != ' ' && str[i] != '	' && str[i] != ',' && str[i])
			i++;
	}
	if (!(split = (char**)malloc(sizeof(char *) * (wc + 2))))
		return (NULL);
	fill_split(split, str);
	free(str);
	return (split);
}
