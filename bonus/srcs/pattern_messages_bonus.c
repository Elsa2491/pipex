/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_messages_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 20:19:29 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/13 03:41:35 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_print_header(void)
{
	ft_printf(2, "\n\e[2m ####################################\e[0m");
	ft_printf(2, "\e[2m####################################\n\n\e[0m");
}

void	ft_print_footer(void)
{
	ft_print_header();
	exit(EXIT_FAILURE);
}
