/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:53 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/15 01:23:17 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H

# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../../../printf/srcs/ft_printf.h"

# define WARNING	 " → Warning\n"
# define CORRECT_ARGV		" Please enter correct arguments:\n"
# define ARROW	"\t→ "

typedef struct s_pipex
{
	char	**all_argvs;
	int		cmd_nb;
	int		infile;
	int		outfile;
	int		code_status;
	pid_t	cmd1[1024];
	pid_t	prev;
	pid_t	cmd2;
	char	*env_path;
	char	**cmd_path;
}		t_pipex;

void	ft_close_processes(t_pipex *pipex, int i);
void	ft_child_process(t_pipex *pipex, char **argv, char **env);
void	ft_handle_parent(t_pipex *pipex, char **argv);
void	ft_parent_process(t_pipex *pipex, char **argv, char **env, int i);

int		ft_strlen(char *str);
int		ft_count_words(char *str);
int		ft_count_size_of_word(char *str);
char	**ft_split(char *str);
void	*ft_free_tab(char **tab);

char	*ft_strncmp(char **env, char *str, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
void	*ft_memset(void *s, int c, unsigned int n);

void	ft_print_too_much_params(void);
void	ft_print_header(void);
void	ft_print_footer(void);

char	*ft_get_cmd_path(t_pipex *pipex, char *argv, char **cmds_path);
int		ft_is_space_only(char *str);
int		ft_is_slash_only(char *str);
void	ft_handle_space_error(char **argv, t_pipex *pipex);
void	ft_handle_slash_error(char **argv, t_pipex *pipex);

void	ft_putstr_fd(char *str, int fd);
void	ft_handle_file_error(char **argv, t_pipex *pipex);
void	ft_handle_cmd_path_error(t_pipex *pipex);
void	ft_handle_pipe_error(t_pipex *pipex);
void	ft_handle_fork_error(t_pipex *pipex, int i);
void	ft_handle_close_error(t_pipex *pipex);
void	ft_handle_dup2_error(t_pipex *pipex);
#endif
