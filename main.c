/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:49:00 by aldferna          #+#    #+#             */
/*   Updated: 2025/02/01 19:39:47 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include "libft/libft.h"

char **search_path(char **env, char *comnd)
{
    char **paths;
    char *aux;
    char *new_path;
    int i;

    i = 0;
    while (env[i] != NULL)
    {
        if (ft_strncmp(env[i], "PATH=", 5) == 0)
            break;
        i++;
    }
    paths = ft_split(env[i] + 5, ':'); //++ en el split; me muevo sin modificar
    i = 0;
    while (paths[i] != NULL)
    {
        aux = ft_strjoin(paths[i], "/");
        new_path = ft_strjoin(aux, comnd);
        free(paths[i]);
        paths[i] = new_path;
        printf ("%s\n", paths[i]); //quitar
        free(aux);
        i++;
    }
    return (paths);
}

int main (int argc, char **argv, char **env)
{
    pid_t pid_1;
    pid_t pid_2;
    int fd_in;
    int fd_out;
    char **comnd1;
    char **comnd2;
    int connect[2];
    char **paths;
    int i;

    if (argc != 5)
        exit (1);
    pipe(connect);
    pid_1 = fork();
    if (pid_1 == -1)
        exit (2);
    if (pid_1 == 0)
    {
        close(connect[0]);
        fd_in = open (argv[1], O_RDONLY);
        if (fd_in == -1)
            exit (3);
        comnd1 = ft_split(argv[2], ' ');
        if (!comnd1)
            exit (4);
        dup2(fd_in, 0);
        close(fd_in);
        dup2(connect[1], 1);
        close(connect[1]);
        paths = search_path(env, comnd1[0]);
        i = 0;
        while (paths[i] != NULL)
        {
            if (access(paths[i], X_OK) == 0) //me faltan flags?
                execve(paths[i], comnd1, env);
            i++;
        }
        exit (5);
    }
    else
    {
        waitpid(pid_1, NULL, 0);
        pid_2 = fork();
        if (pid_2 == -1)
            exit (6);
        if (pid_2 == 0)
        {
            close(connect[1]);
            fd_out = open(argv[4], O_CREAT|O_RDWR|O_TRUNC, 0644);
            if (fd_out == -1)
                exit (7);
            comnd2 = ft_split(argv[3], ' ');
            if (!comnd2)
                exit (8);
            dup2(connect[0], 0);
            close(connect[0]);
            dup2(fd_out, 1);
            close(fd_out);
            paths = search_path(env, comnd2[0]);
            i = 0;
            while (paths[i] != NULL)
            {
                if (access(paths[i], X_OK) == 0) //me faltan flags?
                    execve(paths[i], comnd2, env);
                i++;
            }
            execve("path", comnd2, env);
            exit (9);
        }
        else //aqui algo mas?
        {
            waitpid(pid_2, NULL, 0);
            return (0);
        }
    }
}
