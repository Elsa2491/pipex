/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_access_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/04/20 18:44:27 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_handle_no_file_or_dir(t_pipex *pipex, char *argv, char **path)
{
	ft_putstr_fd(argv, 2);
	ft_free(pipex, argv, path, "No such file or directory\n");
	exit (127);
}

void	ft_handle_directory(t_pipex *pipex, char *argv, char **path)
{
	ft_free(pipex, argv, path, "Is a directory\n");
	exit (126);
}

void	ft_handle_rights(t_pipex *pipex, char *argv, char **path, char *tmp2)
{
	if (tmp2)
		free (tmp2);
	ft_free(pipex, argv, path, "Permission denied\n");
	exit (126);
}
