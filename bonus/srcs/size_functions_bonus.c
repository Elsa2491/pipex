/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:15:31 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/05 22:06:36 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i += 1;
	return (i);
}

int	ft_count_words(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_is_space(str[i]) && str[i] != 58 && str[i] != '\'')
			j += 1;
		while (!ft_is_space(str[i]) && str[i] != 58 && str[i] != '\''
			&& str[i] != '\0')
			i += 1;
		while ((ft_is_space(str[i]) || str[i] == 58 || str[i] == '\'')
			&& str[i] != '\0')
			i += 1;
	}
	return (j);
}

int	ft_count_size_of_word(char *str)
{
	int	i;

	i = 0;
	while (!ft_is_space(str[i]) && str[i] != 58 && str[i] != '\''
		&& str[i] != '\0')
		i += 1;
	return (i);
}
