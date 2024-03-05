/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:34 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/05 20:19:15 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_print_missing_param(void)
{
	ft_print_header();
	ft_printf("\033[%dm\e[1m%s\e\033[0m", 31, WARNING);
	ft_printf(" It seems something went wrong.\n");
	ft_printf(" You must enter 4 parameters. See the example below:\n");
        ft_printf("\033[%dm\e[1m%s\e\033[0m", 32, ARROW);
	ft_printf(" infile cmd1 cmd2 outfile\n");
	ft_print_footer();
}
