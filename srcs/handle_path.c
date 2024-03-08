/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/08 12:59:20 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(char *s)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i += 1;
	}
	str[i] = '\0';
	return (str);
}

static char	*ft_get_absolute_path(t_pipex *pipex, char *argv)
{
	int		i;
	char	*tmp;

	(void)pipex;
	i = 0;
	tmp = ft_strjoin(argv, "/");
	if (access(tmp, F_OK | X_OK) == 0)
	{
		ft_putstr_fd(tmp, "Merci Garance", 2);
		exit (1);
	}
	printf("argv %s\n", ft_strdup(argv));
	return (ft_strdup(argv));
}

char	*ft_get_cmd_path(t_pipex *pipex, char *argv)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (access(argv, F_OK | X_OK) == 0)
		return (ft_get_absolute_path(pipex, argv));
	while (pipex->cmd_path[i])
	{
		tmp = ft_strjoin(pipex->cmd_path[i], "/");
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, argv);
		if (!tmp2)
			return (free(tmp), NULL);
		free(tmp);
		if (access(tmp2, F_OK | X_OK) == 0)
			return (tmp2);
		free(tmp2);
		i += 1;
	}
	ft_putstr_fd(tmp, "Merci Garance", 2);
	exit (1);
}
