/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/18 04:23:57 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_strdup(char *s)
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

static void	ft_free(t_pipex *pipex, char *argv, char **path, char *error)
{
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_free_tab(path);
	ft_free_tab(pipex->cmd_path);
}


static char	*ft_get_absolute_path(t_pipex *pipex, char *argv, char **path)
{
	char	*tmp;

	tmp = ft_strjoin(argv, "/");
	if (!tmp)
		return (NULL);
	if (access(tmp, F_OK) == 0)
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(tmp);
		ft_free_tab(path);
		ft_free_tab(pipex->cmd_path);
		exit (126);
	}
	free(tmp);
	return (ft_strdup(argv));
}

static int	ft_is_a_directory(char *argv)
{
	int	i;
	char	*tmp;

	i = 0;
	tmp = ft_strjoin(argv, "/");
	if (!tmp)
		return (1);
	if (access(tmp, F_OK) == 0)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}

int	ft_strchr(char *str, char c)
{
	int 	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i += 1;
	}
	return (0);
}

char	*ft_get_cmd_path(t_pipex *pipex, char *argv, char **path)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	if (access(argv, F_OK) == -1 && ft_strchr(argv, '/'))
	{
		ft_putstr_fd(argv, 2);
		ft_putstr_fd(": No such file or directory\n", 2); 
		exit (127);
	}
	if (access(argv, F_OK) == 0 && (ft_strchr(argv, '/') || (argv[0] == '.' && argv[1] == '.' && argv[2] == '/') || (argv[0] == '.' && argv[1] == '/')))
	{
		if (ft_is_a_directory(argv))
		{
			ft_free(pipex, argv, path, "Is a directory\n");
			exit (126);
		}	
		if (access(argv, X_OK) != 0)
		{
			ft_free(pipex, argv, path, "Permission denied\n");
			exit (126);
		}
		else
			return (ft_get_absolute_path(pipex, argv, path));
	}
	while (pipex->cmd_path && pipex->cmd_path[i])
	{
		tmp = ft_strjoin(pipex->cmd_path[i], "/");
		if (!tmp)
			return (NULL);
		tmp2 = ft_strjoin(tmp, argv);
		if (!tmp2)
			return (free(tmp), NULL);
		free(tmp);
		if (access(tmp2, F_OK) == 0)
		{
			if (access(tmp2, X_OK) == 0)
				return (tmp2);
			else
			{
				free(tmp2);
				ft_free(pipex, argv, path, "Permission denied\n");
				exit (126);
			}
		}
		free(tmp2);
		i += 1;
	}
	ft_free(pipex, argv, path, "command not found\n");
	exit (127);
}
