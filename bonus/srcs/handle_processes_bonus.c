/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processes_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/20 15:05:17 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_redirections(t_pipex *pipex, char **argv, char **env)
{
	if (pipex->i == 0)
		ft_child_process(pipex, argv, env);
	else if (pipex->i == pipex->argc - 3)
		ft_parent_process(pipex, argv, env);
	else
	{
		if (dup2(pipex->prev_pipe[0], STDIN_FILENO) == -1)
			ft_handle_dup2_error(pipex);
		if (dup2(pipex->curr_pipe[1], STDOUT_FILENO) == -1)
			ft_handle_dup2_error(pipex);
	}
}

void	ft_close_processes(t_pipex *pipex)
{
	int	status;

	close(pipex->prev_pipe[0]);
	close(pipex->prev_pipe[1]);
	close(pipex->curr_pipe[0]);
	close(pipex->curr_pipe[1]);
	while (errno != ECHILD)
	{
		if (pipex->cmd2 == waitpid(-1, &status, 0))
		{
			if (WIFEXITED(status))
				pipex->code_status = WEXITSTATUS(status);
		}
	}
}

void	ft_handle_child(t_pipex *pipex, char **argv)
{
	if (dup2(pipex->infile, STDIN_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->infile) == -1)
		ft_handle_close_error(pipex);
	if (close(pipex->prev_pipe[0]) == -1)
		ft_handle_close_error(pipex);
	if (dup2(pipex->curr_pipe[1], STDOUT_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->curr_pipe[1]) == -1)
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

	ft_handle_child(pipex, argv);
	cmd2 = ft_split(argv[pipex->argc]);
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
		ft_handle_file_error(&argv[pipex->argc - 1], pipex);
	if (dup2(pipex->outfile, STDOUT_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->outfile) == 1)
		ft_handle_close_error(pipex);
	if (close(pipex->curr_pipe[1]) == -1)
		ft_handle_close_error(pipex);
	if (dup2(pipex->prev_pipe[0], STDIN_FILENO) == -1)
		ft_handle_dup2_error(pipex);
	if (close(pipex->prev_pipe[0]) == -1)
		ft_handle_close_error(pipex);
	if (ft_is_space_only(argv[pipex->argc]))
		ft_handle_space_error(&argv[pipex->argc], pipex);
	if (ft_is_slash_only(argv[pipex->argc]))
		ft_handle_slash_error(&argv[pipex->argc], pipex);
}

void	ft_parent_process(t_pipex *pipex, char **argv, char **env)
{
	char	**cmd1;
	char	*cmd1_path;

	pipex->outfile = open(argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0755);
	ft_handle_parent(pipex, argv);
	cmd1 = ft_split(argv[pipex->argc - 1]);
	if (!cmd1)
	{
		ft_free_tab(pipex->cmd_path);
		exit (1);
	}
	cmd1_path = ft_get_cmd_path(pipex, cmd1[0], cmd1);
	(execve(cmd1_path, cmd1, env), perror(cmd1_path), free(cmd1_path));
	ft_free_tab(pipex->cmd_path);
}
