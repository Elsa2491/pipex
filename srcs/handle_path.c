/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/11 15:08:48 by eltouma          ###   ########.fr       */
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

int	ft_is_space_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= 9 && str[i] <= 13) && str[i] != 32)
			return (0);
		i += 1;
	}
	return (1);
}

/*
int	ft_is_slash_only(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 47) 
			return (0);
		i += 1;
	}
	return (1);
}


int	ft_is_at_least_one_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == 47)
			return (1);
		i += 1;
	}
	return (0);
}
*/ 
static char	*ft_get_absolute_path(t_pipex *pipex, char *argv)
{
	char	*tmp;

	(void)pipex;
/*	if (ft_is_slash_only(argv))
	{
		ft_printf(1, "is_only_slash %d\n", ft_is_slash_only(argv));
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": is a directory\n", 2);
		exit (1);
	}
	if (ft_is_at_least_one_slash(argv))
	{
		ft_printf(1, "is_at_least_ONE_slash %d\n", ft_is_at_least_one_slash(argv));
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit (1);
	}*/
	tmp = ft_strjoin(argv, "/");
	if (access(tmp, F_OK | X_OK) == 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit (1);
	}
//	ft_printf(2, "argv %s\n", ft_strdup(argv));
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
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit (1);
}

