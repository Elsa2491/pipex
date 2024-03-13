/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 19:31:34 by eltouma           #+#    #+#             */
/*   Updated: 2024/03/13 03:35:01 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_print_missing_param(void)
{
	ft_print_header();
	ft_printf(2, "\033[%dm\e[1m%s\e\033[0m", 31, WARNING);
	ft_printf(2, " It seems something went wrong.\n");
	ft_printf(2, " You must enter 4 parameters. See the example below:\n");
	ft_printf(2, "\033[%dm\e[1m%s\e\033[0m", 32, ARROW);
	ft_printf(2, " \033[%dm./pipex\033[0m infile cmd1 cmd2 outfile\n", 33);
	ft_print_footer();
}
