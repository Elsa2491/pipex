/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_processes_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/20 23:58:53 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_processes(t_pipex *pipex)
{
	close(pipex->prev_pipe[0]);
	close(pipex->prev_pipe[1]);
	close(pipex->curr_pipe[0]);
	close(pipex->curr_pipe[1]);
}

void	ft_waitpid(t_pipex *pipex)
{
	int	status;

	ft_close_processes(pipex);
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
	if (pipex->is_here_doc)
	{
		pipex->here_doc = open(argv[1], O_RDONLY, 0755);
		if (pipex->here_doc == -1)
			ft_handle_file_error(&argv[1], pipex);
		if (dup2(pipex->here_doc, STDIN_FILENO) == -1)
			ft_handle_dup2_error(pipex);
		if (close(pipex->here_doc) == -1)
			ft_handle_close_error(pipex);
	}
	else
	{
		pipex->infile = open(argv[1], O_RDONLY, 0755);
		if (pipex->infile == -1)
			ft_handle_file_error(&argv[1], pipex);
		if (dup2(pipex->infile, STDIN_FILENO) == -1)
			ft_handle_dup2_error(pipex);
		if (close(pipex->infile) == -1)
			ft_handle_close_error(pipex);
	}
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

	cmd2 = ft_split(argv[pipex->i + 2 + pipex->is_here_doc]);
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
	pipex->outfile = open(argv[pipex->argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0755);
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
	if (ft_is_space_only(argv[pipex->argc - 1]))
		ft_handle_space_error(&argv[pipex->argc - 1], pipex);
	if (ft_is_slash_only(argv[pipex->argc - 1]))
		ft_handle_slash_error(&argv[pipex->argc - 1], pipex);
}

void	ft_handle_processes(t_pipex *pipex, char **argv, char **env)
{
	printf("ici\n");
	printf("%d\n", pipex->is_here_doc);
	if (pipex->i == 0)
		ft_handle_child(pipex, argv);
	else if (pipex->i == pipex->argc - 4 + pipex->is_here_doc)
		ft_handle_parent(pipex, argv);
	else
	{
		if (dup2(pipex->prev_pipe[0], STDIN_FILENO) == -1)
			ft_handle_dup2_error(pipex);
		if (dup2(pipex->curr_pipe[1], STDOUT_FILENO) == -1)
			ft_handle_dup2_error(pipex);
		if (ft_is_space_only(argv[pipex->i + pipex->is_here_doc]))
			ft_handle_space_error(&argv[pipex->i + pipex->is_here_doc], pipex);
		if (ft_is_slash_only(argv[pipex->i + pipex->is_here_doc]))
			ft_handle_slash_error(&argv[pipex->i + pipex->is_here_doc], pipex);

	}
	ft_close_processes(pipex);
	ft_waitpid(pipex);
	ft_child_process(pipex, argv, env);
}
