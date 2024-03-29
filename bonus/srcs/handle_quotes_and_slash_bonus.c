/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/18 02:17:56 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_handle_quotes_and_slash(char *argv)
{
	int     i;
	int     j;
	char    *str;

	i = 0;
	j = 0;
	if (!argv)
		return (NULL);
	str = (char *)malloc(sizeof(char) * ft_strlen(argv) + 1);
	if (!str)
		return (NULL);
	while (argv[i] != '\0')
	{
		while (argv[i] == '\'' || argv[i] == '\"' || argv[i] == '\\')
			i += 1;
		str[j] = argv[i];
		j += 1;
		i += 1;
	}
	str[j] = '\0';
	return (str);
}

void	ft_handle_quotes_error(char **argv, t_pipex *pipex)
{
	ft_putstr_fd(*argv, 2);
	free(*argv);
	ft_free_tab(pipex->cmd_path);
	exit (127);
}
