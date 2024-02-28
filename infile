/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:15:31 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/27 14:42:57 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i += 1;
	return (i);
}

int	ft_count_words(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] != c)
			j += 1;
		while (str[i] != c && str[i] != '\0')
			i += 1;
		while (str[i] == c && str[i] != '\0')
			i += 1;
	}
	return (j);
}

int	ft_count_size_of_word(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i += 1;
	return (i);
}
