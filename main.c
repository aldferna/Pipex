/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:49:00 by aldferna          #+#    #+#             */
/*   Updated: 2025/02/03 18:39:57 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

char	**search_path(char **env, char *comnd)
{
	char	**paths;
	char	*aux;
	char	*new_path;
	int		i;

	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (env[i] == NULL)
	{
		write(2, "Path not found\n", 16);
		exit(10);
	}
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while (paths[i] != NULL)
	{
		aux = ft_strjoin(paths[i], "/");
		new_path = ft_strjoin(aux, comnd);
		free(paths[i]);
		paths[i] = new_path;
		free(aux);
		i++;
	}
	return (paths);
}

void	first_child(int *connect, char **argv, char **env)
{
	int		fd_in;
	char	**paths;
	int		i;
	char	**comnd1;

	close(connect[0]);
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0)
	{
		perror("error input file");
		exit(3);
	}
	comnd1 = ft_split(argv[2], ' ');
	if (!comnd1)
		exit(4);
	dup2(fd_in, 0);
	close(fd_in);
	dup2(connect[1], 1);
	close(connect[1]);
	if ((ft_strchr(comnd1[0], '/') != NULL) && (access(comnd1[0], X_OK) == 0))
		execve(comnd1[0], comnd1, env);
	else
	{
		paths = search_path(env, comnd1[0]);
		i = 0;
		while (paths[i] != NULL)
		{
			if (access(paths[i], R_OK | X_OK) == 0)
				execve(paths[i], comnd1, env);
			i++;
		}
	}
	perror("error command 1");
	exit(5);
}

void	second_child(int *connect, char **argv, char **env)
{
	int		fd_out;
	char	**paths;
	int		i;
	char	**comnd2;

	close(connect[1]);
	fd_out = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror("error output file");
		exit(7);
	}
	comnd2 = ft_split(argv[3], ' ');
	if (!comnd2)
		exit(8);
	dup2(connect[0], 0);
	close(connect[0]);
	dup2(fd_out, 1);
	close(fd_out);
	if ((ft_strchr(comnd2[0], '/') != NULL) && (access(comnd2[0], X_OK) == 0))
		execve(comnd2[0], comnd2, env);
	else
	{
		paths = search_path(env, comnd2[0]);
		i = 0;
		while (paths[i] != NULL)
		{
			if (access(paths[i], R_OK | X_OK) == 0)
				execve(paths[i], comnd2, env);
			i++;
		}
	}
	perror("error command 2");
	exit(9);
}

int	main(int argc, char **argv, char **env)
{
	pid_t	pid_1;
	pid_t	pid_2;
	int		connect[2];

	if (argc != 5 || argv[1][0] == '\0' || argv[2][0] == '\0'
		|| argv[3][0] == '\0' || argv[4][0] == '\0')
	{
		write(1, "empty param\n", 12);
		exit(1);
	}
	pipe(connect);
	pid_1 = fork();
	if (pid_1 == -1)
		exit(2);
	if (pid_1 == 0)
		first_child(connect, argv, env);
	else
	{
		pid_2 = fork();
		if (pid_2 == -1)
			exit(6);
		if (pid_2 == 0)
			second_child(connect, argv, env);
		else
		{
			close(connect[1]);
			close(connect[0]);
			waitpid(pid_1, NULL, 0);
			waitpid(pid_2, NULL, 0);
			return (0);
		}
	}
}
