/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/19 15:29:37 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned char	*pipex;

	pipex = s;
	while (n > 0)
	{
		*(pipex + n - 1) = c;
		n -= 1;
	}
	return (pipex);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		ft_print_missing_param();
	ft_memset(&pipex, 0, sizeof(t_pipex));
	ft_get_path(&pipex, env);
	if (pipe(pipex.fd_pipe) == -1)
		ft_handle_pipe_error(&pipex);
	pipex.pid1 = fork();
	if (pipex.pid1 == -1)
		ft_handle_fork_error(&pipex);
	if (pipex.pid1 == 0)
		ft_exec_cmd1(&pipex, argv, env);
	else if (pipex.pid1 > 0)
		ft_exec_cmd2(&pipex, argv, env);
	ft_free_tab(pipex.cmd_path);
	ft_close_processes(&pipex);
	return (pipex.code_status);
}
