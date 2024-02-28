/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:07:39 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/28 22:08:09 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

void	*ft_memset(void *s, int c, unsigned int n)
{
	unsigned char *pipex;

	pipex = s;
	while (n > 0)
	{
		*(pipex + n - 1) = c;
		n -= 1;
	}
	return (pipex);
}
