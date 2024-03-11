/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/11 15:10:38 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_is_spaces_and_slash(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != 32 && str[i] != 47)
			return (0);
		i += 1;
	}
	return (1);
}

int     ft_is_slash_only(char *str)
{
        int     i;

        i = 0;
        while (str[i] != '\0')
        {
                if (str[i] != 47) 
                        return (0);
                i += 1;
        }
        return (1);
}

int     ft_is_at_least_one_slash(char *str)
{
        int     i;

        i = 0;
        while (str[i] != '\0')
        {
                if (str[i] == 47)
                        return (1);
                i += 1;
        }
        return (0);
}

void	ft_child_process(t_pipex *pipex, char **argv, char **env)
{
	int		infile;
	char	*cmd;
	char	**args;

	//dprintf(2, "id premier enfant : %d\n", getpid());
	infile = open(argv[1], O_RDONLY, 0755);
	if (infile == -1)
		perror(argv[1]);
	dup2(infile, 0);
	close(infile);
	close(pipex->fd_pipe[0]);
	dup2(pipex->fd_pipe[1], 1);
	close(pipex->fd_pipe[1]);
	if (ft_is_space_only(argv[2]))
	{
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd(" : command not found\n", 2);
		exit (1);
	}
/*	if (ft_is_spaces_and_slash(argv[2]))
	{
		ft_putstr_fd(argv[2], 2);
		ft_putstr_fd(" : No such file or directory\n", 2);
		ft_putstr_fd("je rentre dans spaces_slash\n", 2);
		exit (1);
	}*/
	args = ft_split(argv[2]);
	if (!args)
		exit (1);
	cmd = ft_get_cmd_path(pipex, args[0]);
	execve(cmd, args, env);
	perror(cmd);
	//	ft_printf(2, "Error in child process 1\n");
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
		if (ft_is_space_only(argv[3]))
		{
			ft_putstr_fd(argv[3], 2);
			ft_putstr_fd(" : command not found\n", 2);
			exit (1);
		}
	 	if (ft_is_slash_only(argv[3]))
                {
                        ft_putstr_fd(argv[3], 2);
                        ft_putstr_fd(" : Is a directory\n", 2);
                        exit (1);
                }

		if (ft_is_at_least_one_slash(argv[3]))
		{
			ft_putstr_fd(argv[3], 2);
			ft_putstr_fd(" : No such file or directory\n", 2);
			exit (1);
		}
		args = ft_split(argv[3]);
		cmd = ft_get_cmd_path(pipex, args[0]);
		execve(cmd, args, env);
		perror(cmd);
		//		ft_printf(2, "Error in child process 2\n");
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

	if (argc != 5)
		ft_print_missing_param();
	ft_memset(&pipex, 0, sizeof(t_pipex));
	pipex.env_path = ft_strncmp(env, "PATH=", 5);
	if (!pipex.env_path)
		exit (1);
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
