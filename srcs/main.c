/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/12 10:57:24 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_child_process(t_pipex *pipex, char **argv, char **env)
{
	int		infile;
	char	**cmd2;
	char	*cmd2_path;

	dprintf(1, "id premier enfant : %d\n", getpid());
	infile = open(argv[1], O_RDONLY, 0755);
	if (infile == -1)
		perror(argv[1]);
	dup2(infile, 0);
	close(infile);
	close(pipex->fd_pipe[0]);
	dup2(pipex->fd_pipe[1], 1);
	close(pipex->fd_pipe[1]);
	if (ft_is_space_only(argv[2]))
	{
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd(" : command not found\n", 2);
		ft_free_tab(pipex->cmd_path);
		exit (1);
	}
	if (ft_is_slash_only(argv[2]))
	{
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd(" : Is a directory\n", 2);
		ft_free_tab(pipex->cmd_path);
		exit (1);
	}
	cmd2 = ft_split(argv[2]);
	if (!cmd2)
		exit (1);
	cmd2_path = ft_get_cmd_path(pipex, cmd2[0], cmd2);
	execve(cmd2_path, cmd2, env);
	perror(cmd2_path);
	exit (1);
}

void	ft_parent_process(t_pipex *pipex, char **argv, char **env)
{
	int		outfile;
	char	**cmd1;
	char	*cmd1_path;

	pipex->cmd2 = fork();
	if (pipex->cmd2 == 0)
	{
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (outfile == -1)
			perror(argv[4]);
		dup2(outfile, 1);
		close(outfile);
		close(pipex->fd_pipe[1]);
		dup2(pipex->fd_pipe[0], 0);
		close(pipex->fd_pipe[0]);
		if (ft_is_space_only(argv[3]))
		{
			ft_putstr_fd(argv[3], 2);
			ft_putstr_fd(" : command not found\n", 2);
			ft_free_tab(pipex->cmd_path);
			exit (1);
		}
		if (ft_is_slash_only(argv[3]))
		{
			ft_putstr_fd(argv[3], 2);
			ft_putstr_fd(" : Is a directory\n", 2);
			ft_free_tab(pipex->cmd_path);
			exit (1);
		}
		cmd1 = ft_split(argv[3]);
		cmd1_path = ft_get_cmd_path(pipex, cmd1[0], cmd1);
		execve(cmd1_path, cmd1, env);
		perror(cmd1_path);
		exit (1);
	}
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	waitpid(pipex->cmd1, NULL, 0);
	waitpid(pipex->cmd2, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_print_missing_param();
	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.env_path = ft_strncmp(env, "PATH=", 5);
	if (!pipex.env_path)
		exit (1);
	pipex.cmd_path = ft_split(pipex.env_path);
	if (!pipex.cmd_path)
	{
		close(pipex.fd_pipe[0]);
		close(pipex.fd_pipe[1]);
		waitpid(pipex.cmd1, NULL, 0);
		waitpid(pipex.cmd2, NULL, 0);
		exit (1);
	}
	if (pipe(pipex.fd_pipe) == -1)
	{
		close(pipex.fd_pipe[0]);
		close(pipex.fd_pipe[1]);
		waitpid(pipex.cmd1, NULL, 0);
		waitpid(pipex.cmd2, NULL, 0);
		ft_free_tab(pipex.cmd_path);
		return (-1);
	}
	pipex.cmd1 = fork();
	if (pipex.cmd1 == -1)
	{
		close(pipex.fd_pipe[0]);
		close(pipex.fd_pipe[1]);
		waitpid(pipex.cmd1, NULL, 0);
		waitpid(pipex.cmd2, NULL, 0);
		ft_free_tab(pipex.cmd_path);
		return (-1);
	}
	if (pipex.cmd1 == 0)
		ft_child_process(&pipex, argv, env);
	else if (pipex.cmd1 > 0)
		ft_parent_process(&pipex, argv, env);
	ft_free_tab(pipex.cmd_path);
	return (0);
}
