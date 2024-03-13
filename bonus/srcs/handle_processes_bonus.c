/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processes_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/13 04:09:57 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_processes(t_pipex *pipex)
{
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	waitpid(pipex->cmd1, NULL, 0);
	waitpid(pipex->cmd2, &pipex->code_status, 0);
}

void	ft_handle_child(t_pipex *pipex, char **argv)
{
	if (pipex->infile == -1)
		ft_handle_file_error(&argv[1], pipex);
	if (dup2(pipex->infile, 0) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->infile) == -1)
		ft_handle_close_error(pipex);
	if (close(pipex->fd_pipe[0]) == -1)
		ft_handle_close_error(pipex);
	if (dup2(pipex->fd_pipe[1], 1) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->fd_pipe[1]) == -1)
		ft_handle_close_error(pipex);
	if (ft_is_space_only(argv[2]))
		ft_handle_space_error(&argv[2], pipex);
	if (ft_is_slash_only(argv[2]))
		ft_handle_slash_error(&argv[2], pipex);
}

void	ft_child_process(t_pipex *pipex, char **argv, char **env)
{
	char	**cmd2;
	char	*cmd2_path;

	pipex->infile = open(argv[1], O_RDONLY, 0755);
	ft_handle_child(pipex, argv);
	cmd2 = ft_split(argv[2]);
	if (!cmd2)
	{
		ft_free_tab(pipex->cmd_path);
		exit (1);
	}
	cmd2_path = ft_get_cmd_path(pipex, cmd2[0], cmd2);
	execve(cmd2_path, cmd2, env);
	perror(cmd2_path);
	free(cmd2_path);
	ft_free_tab(pipex->cmd_path);
	exit (1);
}

void	ft_handle_parent(t_pipex *pipex, char **argv)
{
	if (pipex->outfile == -1)
		ft_handle_file_error(&argv[4], pipex);
	if (dup2(pipex->outfile, 1) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->outfile) == 1)
		ft_handle_close_error(pipex);
	if (close(pipex->fd_pipe[1]) == -1)
		ft_handle_close_error(pipex);
	if (dup2(pipex->fd_pipe[0], 0) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->fd_pipe[0]) == -1)
		ft_handle_close_error(pipex);
	if (ft_is_space_only(argv[3]))
		ft_handle_space_error(&argv[3], pipex);
	if (ft_is_slash_only(argv[3]))
		ft_handle_slash_error(&argv[3], pipex);
}

void	ft_parent_process(t_pipex *pipex, char **argv, char **env)
{
	char	**cmd1;
	char	*cmd1_path;

	pipex->cmd2 = fork();
	if (pipex->cmd2 == -1)
		ft_handle_fork_error(pipex);
	if (pipex->cmd2 == 0)
	{
		pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0755);
		ft_handle_parent(pipex, argv);
		cmd1 = ft_split(argv[3]);
		if (!cmd1)
		{
			ft_free_tab(pipex->cmd_path);
			exit (1);
		}
		cmd1_path = ft_get_cmd_path(pipex, cmd1[0], cmd1);
		(execve(cmd1_path, cmd1, env), perror(cmd1_path), free(cmd1_path));
		ft_free_tab(pipex->cmd_path);
		exit (1);
	}
	ft_close_processes(pipex);
}
