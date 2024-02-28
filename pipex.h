/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 15:17:53 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/27 20:15:14 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "printf/ft_printf.h"

typedef struct s_struct
{
    pid_t     pid_tab[1024];
    int       *fd[];
}               t_struct;


int		ft_strlen(char *str);
int		ft_count_words(char *str, char c);
int		ft_count_size_of_word(char *str, char c);
char	**ft_split(char *str, char c);
#endif
