/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frlindh <frlindh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:11:48 by frlindh           #+#    #+#             */
/*   Updated: 2019/10/16 14:13:03 by frlindh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_split(char **split, char const *str, char c)
{
	int		i;
	int		j;
	int		a;

	i = 0;
	a = 0;
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		j = 0;
		while (str[i + j] != c && str[i + j])
			j++;
		if (!(split[a] = (char *)malloc(sizeof(char) * (j + 1))))
			return ;
		j = 0;
		while (str[i] != c && str[i])
			split[a][j++] = str[i++];
		split[a][j] = '\0';
		if (str[i - 1] != c)
			a++;
	}
	split[a] = NULL;
}

char		**ft_split(char const *str, char c)
{
	int		wc;
	int		i;
	char	**split;

	i = 0;
	wc = 0;
	if (str == NULL)
		return (NULL);
	while (str[i])
	{
		while (str[i] == c && str[i])
			i++;
		wc++;
		while (str[i] != c && str[i])
			i++;
	}
	if (!(split = (char**)malloc(sizeof(char *) * (wc + 1))))
		return (NULL);
	fill_split(split, str, c);
	return (split);
}
