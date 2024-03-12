/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:27 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/12 22:11:11 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_fill_tab(char *str)
{
	int		i;
	int		size;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	size = ft_count_size_of_word(str);
	s = (char *)malloc(sizeof(char) * size + 1);
	if (!s)
		return (NULL);
	while (str[i] != '\0' && str[i] != 58 && str[i] != 32
		&& !(str[i] >= 9 && str[i] <= 13))
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '\0';
	return (s);
}

static char	**ft_return_tab(char *str)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (ft_count_words(str) + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i += 1;
	}
	free(tab);
	tab = NULL;
	return (NULL);
}

char	**ft_split(char *str)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	tab = ft_return_tab(str);
	tab[ft_count_words(str)] = NULL;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32 && str[i] != 58)
		{
			tab[j] = ft_fill_tab(&str[i]);
			if (!tab[j++])
				return (ft_free_tab(tab));
			while (str[i] != '\0' && str[i] != 58 && str[i] != 32
				&& !(str[i] >= 9 && str[i] <= 13))
				i += 1;
		}
		else
			i += 1;
	}
	return (tab);
}
