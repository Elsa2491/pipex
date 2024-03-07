/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/07 18:08:48 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

char	*ft_get+absolute_path(t_pipex *pipex, char *argv)
{
	int
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
		perror(argv[1]);
	dup2(infile, 0);
	close(infile);
	close(pipex->fd_pipe[0]);
	dup2(pipex->fd_pipe[1], 1);
	close(pipex->fd_pipe[1]);
	args = ft_split(argv[2]);
	cmd = ft_get_cmd_path(pipex, args[0]);
	execve(cmd, args, env);
	perror(cmd);
	ft_printf(2, "Error in child process 1\n");
	exit (1);
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
			perror(argv[4]);
		dup2(outfile, 1);
		close(outfile);
		close(pipex->fd_pipe[1]);
		dup2(pipex->fd_pipe[0], 0);
		close(pipex->fd_pipe[0]);
		args = ft_split(argv[3]);
		cmd = ft_get_cmd_path(pipex, args[0]);
		execve(cmd, args, env);
		perror(cmd);
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

