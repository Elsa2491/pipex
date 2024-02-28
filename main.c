/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltouma <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 14:46:15 by eltouma           #+#    #+#             */
/*   Updated: 2024/02/28 01:26:57 by eltouma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int     main(int argc, char **argv, char **env)
{
        pid_t   cmd1;
        pid_t   cmd2;
        int     fd_pipe[2];

        pipe(fd_pipe);
        cmd1 = fork();
        if (cmd1 == 0)
        {
                int     infile;
                infile = open("infile", O_RDONLY, 0755);
                printf("Je suis l'enfant 1\n");
                dup2(infile, 0);

                close(fd_pipe[0]);
                dup2(fd_pipe[1], 1);
                close(fd_pipe[1]);
                char    *cmd[] = {"cat", NULL};
                execve("/usr/bin/cat", cmd, NULL);
        }
        else
        {
                cmd2 = fork();
                if (cmd2 == 0)
                {
                        int     outfile;
                        outfile = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0755);
                        dup2(outfile, 1);

                        printf("Je suis l'enfant 2\n");
                        close(fd_pipe[1]);
                        dup2(fd_pipe[0], 0);
                        close(fd_pipe[0]);
                        char    *cmd[] = {"wc", NULL};
                        execve("/usr/bin/wc", cmd, NULL);
                }
        }
        close(fd_pipe[0]);
        close(fd_pipe[1]);
        waitpid(cmd1, NULL, 0);
        waitpid(cmd2, NULL, 0);
        return (0);
}

