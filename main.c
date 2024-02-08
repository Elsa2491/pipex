/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/08 21:06:07 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	main(int argc, char **argv, char **env)
{
	int	fd[2];
	int	id;
	int	id2;
	//	int	file1;
	//	int	file2;
	int	error;
	int	code_status;

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
		close(fd[0]);
		char *arr[] = {"/usr/bin/echo", "Je suis demunie Alix", NULL};
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
		wait(&id);
		id2 = fork();		
		close(fd[1]);
		char *arr[] = {"/usr/bin/echo", "Je suis demunie Alix", NULL};
		dup2(fd[0], 0);
		close(fd[0]);
		error = execve(arr[0], argv, env);
		if (WIFEXITED(id))
		{
			code_status = WEXITSTATUS(id);
			if (code_status == 0)
				ft_printf("Success\n");
			else
				ft_printf("Failure with status code: %d\n", code_status);
		}

	}
	return (0);
}
