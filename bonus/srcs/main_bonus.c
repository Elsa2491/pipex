/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/20 21:33:07 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

// changer cmd1 et cmd2 par pid
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < 5)
		ft_print_missing_param(); // change msg
	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.argc = argc;
	ft_get_env(&pipex, env);
//	pipex.infile = open(argv[1], O_RDONLY, 0755);
//	if (pipex.infile == -1)
//		ft_handle_file_error(&argv[1], &pipex);
	if (pipe(pipex.prev_pipe) == -1)
		ft_handle_pipe_error(&pipex);
	while (pipex.i < pipex.argc - 3)
	{
		if (pipe(pipex.curr_pipe) == -1)
			ft_handle_pipe_error(&pipex);
		pipex.cmd1 = fork();
		pipex.cmd1 = -1;
		if (pipex.cmd1 == -1)
			ft_handle_fork_error(&pipex);
		if (pipex.cmd1 == 0)
			ft_handle_processes(&pipex, argv, env);
		else if (pipex.cmd1 > 0)
		{
			close(pipex.prev_pipe[0]);
			close(pipex.prev_pipe[1]);
			pipex.prev_pipe[0] = pipex.curr_pipe[0];
			pipex.prev_pipe[1] = pipex.curr_pipe[1];
		}
		pipex.i += 1;
	}
	ft_close_processes(&pipex);
	ft_free_tab(pipex.cmd_path);
	pipex.i = 0;
	while (pipex.i++ < argc - 3)
		ft_waitpid(&pipex);
	return (pipex.code_status);
}
