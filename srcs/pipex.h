/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:53 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/08 20:34:42 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../printf/srcs/ft_printf.h"

# define WARNING	 " → Warning\n"
# define CORRECT_ARGV		" Please enter correct arguments:\n"
# define ARROW	"\t→ "

typedef struct s_pipex
{
	int		fd_pipe[2];
	int		exec;
	pid_t	cmd1;
	pid_t	cmd2;
	char	*env_path;
	char	**cmd_path;
}		t_pipex;

int		ft_strlen(char *str);
int		ft_count_words(char *str);
int		ft_count_size_of_word(char *str);
char	*ft_strncmp(char **env, char *str, int n);
int	ft_strcmp(char *argv, char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
void	*ft_memset(void *s, int c, unsigned int n);
char	**ft_split(char *str);
void	*ft_free_tab(char **tab);
void	ft_print_missing_param(void);
void	ft_print_header(void);
void	ft_print_footer(void);
//void	ft_putstr_fd(char *str, char *error, int fd);
void	ft_putstr_fd(char *str, int fd);
char	*ft_get_cmd_path(t_pipex *pipex, char *argv);
int		ft_is_space_only(char *str);
#endif
