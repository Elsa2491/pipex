/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/27 20:14:18 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	pid_t	id;
	int	error;
	char	*all_argv;
	int	nb_cmds;
	int	i;
	t_struct	pid;

	i = 0;
	all_argv  = argv[2];
	nb_cmds = argc - 3;
	if (pipe(fd) == -1)
		return (-1);
	id = 0;
	id = fork();
	if (id == -1)
		return (-1);
	while (i < nb_cmds)
	{
		if (id == 0)
		{
			dprintf(2, "\nid premier enfant : %d\n", getpid());
			close(fd[0]);
//			char	*path[] = {"/usr/bin/echo", argv[0], NULL};
			char	*path[] = {argv[2], argv[1], NULL};
			dup2(fd[1], 1);
			close(fd[1]);
			pid.pid_tab[i] = id;
			dprintf(2, "\ni du premier enfant %d vaut %d\n", getpid(), i);
			error = execve(path[0], path, env);
			if (error == -1)
			{
				ft_printf("Error in child process 1\n");
				exit (1);
			}
		}
		else if (id > 0)
		{
			id = fork();
			if (id == 0)
			{
				dprintf(2, "id deuxieme enfant : %d\n\n", getpid());
				close(fd[1]);
				char	*path[] = {"/usr/bin/wc", NULL};
//				char	*path[] = {argv[3], argv[4], NULL};
				dup2(fd[0], 0);
				close(fd[0]);
//				pid.pid_tab[++i] = id;
				dprintf(2, "\ni du deuxieme enfant %d vaut %d\n", getpid(), i);
				error = execve(path[0], path, env);
				if (error == -1)
				{
					ft_printf("Error in child process 2\n");
					exit (1);
				}
			}
			else
			{
				close(fd[0]);
				close(fd[1]);
			}
//			waitpid(pid.pid_tab[i], NULL, 0);
//			while (wait(NULL) > 0);
		}
		pid.pid_tab[++i] = id;
//		i += 1;
		waitpid(pid.pid_tab[i], NULL, 0);
	}
	waitpid(pid.pid_tab[i], NULL, 0);
//	waitpid(id, NULL, 0);
//	while (wait(NULL) > 0);
	return (0);
}
