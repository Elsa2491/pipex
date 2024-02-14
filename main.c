/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/14 18:53:31 by eltouma          ###   ########.fr       */
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
		char *arr[] = {"/usr/bin/echo", NULL};
		dup2(fd[1], 1);
		close(fd[1]);
		error = execve(arr[0], argv, env);
		if (error == -1)
		{
			ft_printf("Error in child process\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		id = fork();		
		close(fd[1]);
		if (id == 0)
		{
			dprintf(2, "id deuxieme enfant : %d\n", getpid());
			close(fd[1]);
			char *arr[] = {"/usr/bin/cat", NULL};
			dup2(fd[0], 0);
			close(fd[0]);
			error = execve(arr[0], argv, env);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
//			wait(&id);
		}
		wait(&id);
	}
	while(wait(NULL) > 0)
	return (0);
}
