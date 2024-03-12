/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dup2_and_open_errors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 15:42:39 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/12 16:00:30 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_handle_close_error(t_pipex *pipex)
{
	ft_putstr_fd("close failed\n", 2);
	ft_free_tab(pipex->cmd_path);
	close(pipex->outfile);
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	exit (1);
}

void	ft_handle_dup2_error(t_pipex *pipex)
{
	ft_putstr_fd("dup2 failed\n", 2);
	ft_free_tab(pipex->cmd_path);
	if (close(pipex->outfile) == -1)
		ft_handle_close_error(pipex);
	if (close(pipex->fd_pipe[0]) == -1)
		ft_handle_close_error(pipex);
	if (close(pipex->fd_pipe[1]) == -1)
		ft_handle_close_error(pipex);
	exit (1);
}
