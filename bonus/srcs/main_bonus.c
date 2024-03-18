/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/14 19:21:22 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int	i;

	i = 0;
	
	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.all_argvs = argv + 2;
	pipex.cmd_nb = argc - 3;
	if (pipex.cmd_nb >= 1024)
		ft_print_too_much_params();
	pipex.env_path = ft_strncmp(env, "PATH=", 5);
	if (pipex.env_path)
	{
		pipex.cmd_path = ft_split(pipex.env_path);
		if (!pipex.cmd_path)
			return (1);
	}
	else
		pipex.cmd_path = NULL;
	while (i < pipex.cmd_nb)
	{
		if (pipe(pipex.fd_pipe) == -1)
			ft_handle_pipe_error(&pipex);
		pipex.cmd1[i] = fork();
		if (pipex.cmd1[i] == -1)
			ft_handle_fork_error(&pipex, i);
		if (pipex.cmd1[i] == 0)
			ft_child_process(&pipex, argv, env);
		close(pipex.fd_pipe[1]);
//		if (i != 0)
//		{
			ft_putstr_fd("je rentre la\n", 2);
//			close(pipex.prev);
//		}
		pipex.prev = pipex.fd_pipe[0];
		i += 1;
	}
	i = 0;
	while (i < pipex.cmd_nb)
	{
		ft_close_processes(&pipex, i);
		i += 1;
	}
		
	ft_parent_process(&pipex, argv, env, i);
	ft_free_tab(pipex.cmd_path);
	return (pipex.code_status);
}
