/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/13 04:25:48 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
//	int	i;

	pipex.all_cmd = argc + 2;
	pipex.cmd_nb = argc - 3;
//	i = pipex.all_cmd;
	if (argc < pipex.cmd_nb - 1)
		ft_print_missing_param();
	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.env_path = ft_strncmp(env, "PATH=", 5);
	if (pipex.env_path)
	{
		pipex.cmd_path = ft_split(pipex.env_path);
		if (!pipex.cmd_path)
			return (1);
	}
	else
		pipex.cmd_path = NULL;
	if (pipe(pipex.fd_pipe) == -1)
		ft_handle_pipe_error(&pipex);
	pipex.cmd1 = fork();
	if (pipex.cmd1 == -1)
		ft_handle_fork_error(&pipex);
	if (pipex.cmd1 == 0)
		ft_child_process(&pipex, argv, env);
	if (pipex.cmd1 > 0)
		ft_parent_process(&pipex, argv, env);
	ft_free_tab(pipex.cmd_path);
	return (0);
}
