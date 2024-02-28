/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:53 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/28 15:03:50 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../printf/srcs/ft_printf.h"

typedef struct s_pipex
{
	//pid_t     pid_tab[1024];
	int	fd_pipe[2];
	pid_t	cmd1;
	pid_t	cmd2;
	int	exec;
}               t_pipex;


int		ft_strlen(char *str);
int		ft_count_words(char *str, char c);
int		ft_count_size_of_word(char *str, char c);
char	**ft_split(char *str, char c);
#endif
