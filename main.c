/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/15 17:39:43 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	id;
	//	int	file1;
	//	int	file2;
	int	error;

	(void)argc;
	//		file1 = open(argv[1], O_RDONLY);
	//		file2 = open(argv[4], O_RDWR | O_TRUNC | O_CREAT, 0777);
	//		if (file1 == -1)
	//			return (-1);

	if (pipe(fd) == -1)
		return (-1);
	id = 0;
	id = fork();
	if (id == -1)
		return (-1);
	if (id == 0)
	{

		dprintf(2, "id premier enfant : %d\n", getpid());
		close(fd[0]);
		char *path[] = {"/usr/bin/echo", argv[1], NULL};
		dup2(fd[1], 1);
		close(fd[1]);
		error = execve(path[0], path, env);
		if (error == -1)
		{
			ft_printf("Error in child process\n");
			exit (1);
		}
	}
	else
	{
		id = fork();
		if (id == 0)
		{
			dprintf(2, "id deuxieme enfant : %d\n", getpid());
			close(fd[1]);
			char *path[] = {"/usr/bin/wc", "-l", NULL};
			dup2(fd[0], 0);
			close(fd[0]);
			error = execve(path[0], path, env);
			if (error == -1)
			{
				ft_printf("Error in child process\n");
				exit (1);
			}
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
		}
		while (wait(NULL) > 0);
	}
	while (wait(NULL) > 0);
	return (0);
}
