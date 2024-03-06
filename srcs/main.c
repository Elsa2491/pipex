/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/06 19:59:41 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

// tester avec path absolu
char	*ft_get_cmd_path(t_pipex *pipex, char *argv)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	while (pipex->cmd_path[i])
	{
		tmp = ft_strjoin(pipex->cmd_path[i], "/");
		tmp2 = ft_strjoin(tmp, argv);
		free(tmp);
//		dprintf(2, "ACCESS tmp = %s\n", tmp2);
		if (access(tmp2, F_OK | X_OK) == 0)
			return (tmp2);
		free(tmp2);
		i += 1;
	}
	return (NULL);
}

void	ft_print_error_infile(t_pipex *pipex, char **argv)
{
	if (!ft_strcmp(argv[2], "ls"))
	{
		ft_putstr_fd(argv[2], ": cannot access '", 2);
		ft_putstr_fd(argv[1], "': No such file or directory",  2);
	}
	else if (!ft_strcmp(argv[2], "cp") || (!ft_strcmp(argv[2], "mv")))
	{
		ft_putstr_fd(argv[2], ": cannot stat '", 2);
		ft_putstr_fd(argv[1], "': No such file or directory",  2);
	}
	else if (!ft_strcmp(argv[2], "cat") || !(ft_strcmp(argv[2], "wc")) || !ft_strcmp(argv[2], "cd"))
	{
		ft_putstr_fd(argv[2], ": ", 2);
		ft_putstr_fd(argv[1], ": No such file or directory",  2);
	}
	else if (!ft_strcmp(argv[2], "rm"))
	{
		ft_putstr_fd(argv[2], ": cannot remove '", 2);
		ft_putstr_fd(argv[1], "': No such file or directory",  2);
	}
	else if (!ft_strcmp(argv[2], "rmdir"))
	{
		ft_putstr_fd(argv[2], ": failed to remove '", 2);
		ft_putstr_fd(argv[1], ": No such file or directory",  2);
	}
	ft_printf(2, "\n");
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	ft_free_tab(pipex->cmd_path);
	exit (EXIT_FAILURE);
}

void	ft_child_process(t_pipex *pipex, char **argv, char **env)
{
	int		infile;
	int		i;
	char	*cmd;
	char	**args;

	i = 0;
	dprintf(2, "id premier enfant : %d\n", getpid());
	infile = open(argv[1], O_RDONLY, 0755);
	if (infile == -1)
		ft_print_error_infile(pipex, argv);
	dup2(infile, 0);
	close(infile);
	close(pipex->fd_pipe[0]);
	dup2(pipex->fd_pipe[1], 1);
	close(pipex->fd_pipe[1]);
	args = ft_split(argv[2]);
	cmd = ft_get_cmd_path(pipex, args[0]);
	if (!cmd)
	{
		ft_putstr_fd(argv[2], ": command not found\n", 2);
		exit (1);
	}
	execve(cmd, args, env);
	ft_printf(2, "Error in child process 1\n");
	exit (1);
}

void	ft_print_error_outfile(t_pipex *pipex, char **argv)
{
	ft_putstr_fd(argv[4], ": Is a directory", 2);
	ft_printf(2, "\n");
	close(pipex->fd_pipe[0]);
	close(pipex->fd_pipe[1]);
	ft_free_tab(pipex->cmd_path);
	exit (EXIT_FAILURE);
}

void	ft_parent_process(t_pipex *pipex, char **argv, char **env)
{
	int		outfile;
	char	*cmd;
	char	**args;

	pipex->cmd2 = fork();
	if (pipex->cmd2 == 0)
	{
		outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0755);
		if (outfile == -1)
			ft_print_error_outfile(pipex, argv);
		dup2(outfile, 1);
		close(outfile);
		close(pipex->fd_pipe[1]);
		dup2(pipex->fd_pipe[0], 0);
		close(pipex->fd_pipe[0]);
		args = ft_split(argv[3]);
		cmd = ft_get_cmd_path(pipex, args[0]);
		if (!cmd)
		{
			ft_putstr_fd(argv[3], ": command not found\n", 2);
			exit (1);
		}
		execve(cmd, args, env);
		ft_printf(2, "Error in child process 2\n");
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

	(void)env;
	if (argc != 5)
		ft_print_missing_param();
	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.env_path = ft_strncmp(env, "PATH=", 5);
	pipex.cmd_path = ft_split(pipex.env_path);
	if (pipe(pipex.fd_pipe) == -1)
		return (-1);
	pipex.cmd1 = fork();
	if (pipex.cmd1 == -1)
		return (-1);
	if (pipex.cmd1 == 0)
		ft_child_process(&pipex, argv, env);
	else if (pipex.cmd1 > 0)
		ft_parent_process(&pipex, argv, env);
	ft_free_tab(pipex.cmd_path);
	return (0);
}

