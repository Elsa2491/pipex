/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/28 15:02:35 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	ft_child_process(t_pipex pipex)
{
	int		infile;

	infile = open("infile", O_RDONLY, 0755);
	dprintf(2, "id premier enfant : %d\n", getpid());
	dup2(infile, 0);
	close(infile);
	close(pipex.fd_pipe[0]);
	dup2(pipex.fd_pipe[1], 1);
	close(pipex.fd_pipe[1]);
	char	*cmd[] = {"cat", NULL};
	pipex.exec = execve("/usr/bin/cat", cmd, NULL);
	if (pipex.exec == -1)
	{
		ft_printf("Error in child process 1\n");
		exit (1);
	}
}

void	ft_parent_process(t_pipex pipex)
{
	int		outfile;

	pipex.cmd2 = fork();
	if (pipex.cmd2 == 0)
	{
		outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0755);
		dprintf(2, "id deuxieme enfant : %d\n", getpid());
		dup2(outfile, 1);
		close(outfile);
		close(pipex.fd_pipe[1]);
		dup2(pipex.fd_pipe[0], 0);
		close(pipex.fd_pipe[0]);
		char	*cmd[] = {"wc", NULL};
		pipex.exec = execve("/usr/bin/wc", cmd, NULL);
		if (pipex.exec == -1)
		{
			ft_printf("Error in child process 1\n");
			exit (1);
		}
	}
	close(pipex.fd_pipe[0]);
	close(pipex.fd_pipe[1]);
	waitpid(pipex.cmd1, NULL, 0);
	waitpid(pipex.cmd2, NULL, 0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_pipex		pipex;

	if (pipe(pipex.fd_pipe) == -1)
		return (-1);
	pipex.cmd1 = fork();
	if (pipex.cmd1 == -1)
		return (-1);
	if (pipex.cmd1 == 0)
		ft_child_process(pipex);
	else if (pipex.cmd1 > 0)
		ft_parent_process(pipex);
	return (0);
}
