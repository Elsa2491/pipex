/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:27 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/28 20:26:23 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_fill_tab(char *str, char c)
{
	int		i;
	int		size;
	char	*s;

	i = 0;
	if (!str)
		return (NULL);
	size = ft_count_size_of_word(str, c);
	s = (char *)malloc(sizeof(char) * size + 2);
	if (!s)
		return (NULL);
	while (str[i] != '\0' && str[i] != c)
	{
		s[i] = str[i];
		i += 1;
	}
	s[i] = '/';
	s[i + 1] = '\0';
	return (s);
}

static char	**ft_return_tab(char *str, char c)
{
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (ft_count_words(str, c) + 1));
	if (!tab)
		return (NULL);
	return (tab);
}

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
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

char	**ft_split(char *str, char c)
{
	int		i;
	int		j;
	char	**tab;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	tab = ft_return_tab(str, c);
	tab[ft_count_words(str, c)] = NULL;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			tab[j] = ft_fill_tab(&str[i], c);
			if (!tab[j])
				return (ft_free_tab(tab));
			j += 1;
			while (str[i] != '\0' && str[i] != c)
				i += 1;
		}
		else
			i += 1;
	}
	return (tab);
}
