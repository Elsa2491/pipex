/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:15:12 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/13 17:03:51 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_putstr_fd(char *str, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
}

void	ft_handle_file_error(char **argv, t_pipex *pipex)
{
	perror(*argv);
	ft_free_tab(pipex->cmd_path);
	if (pipex->infile != -1)
		close(pipex->infile);
	if (pipex->outfile != -1)
		close(pipex->outfile);
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	exit (1);
}

void	ft_handle_pipe_error(t_pipex *pipex)
{
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}

void	ft_handle_fork_error(t_pipex *pipex, int i)
{
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	waitpid(pipex->cmd1[i], NULL, 0);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}
