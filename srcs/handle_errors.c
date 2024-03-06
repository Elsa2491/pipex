/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 18:15:12 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/06 01:16:24 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_putstr_fd(char *str, char *error, int fd)
{
	if (!str)
		return ;
	write(fd, str, ft_strlen(str));
	ft_printf(2, "%s", error);
}
