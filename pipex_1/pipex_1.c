/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldferna <aldferna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 13:49:00 by aldferna          #+#    #+#             */
/*   Updated: 2025/02/05 19:30:55 by aldferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_1.h"

char	**search_path(char **env, char *comnd)
{
	char	**paths;
	char	*aux;
	char	*new_path;
	int		i;

	i = 0;
	while ((env[i] != NULL) && (ft_strncmp(env[i], "PATH=", 5) != 0))
		i++;
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

void	exe(char **env, char **comnd)
{
	char	**paths;
	int		i;

	if ((ft_strchr(comnd[0], '/') != NULL) && (access(comnd[0], X_OK) == 0))
		execve(comnd[0], comnd, env);
	else
	{
		paths = search_path(env, comnd[0]);
		i = 0;
		while (paths[i] != NULL)
		{
			if (access(paths[i], R_OK | X_OK) == 0)
				execve(paths[i], comnd, env);
			i++;
		}
		i = 0;
		while (paths[i])
			free(paths[i++]);
		free(paths);
	}
	// perror("error command");
	// exit(5);
}

void	first_command(int *connect, char **argv, char **env)
{
	int		fd_in;
	char	**comnd1;

	close(connect[0]);
	fd_in = open(argv[INFILE], O_RDONLY);
	if (fd_in < 0)
	{
		perror("error input file");
		exit(3);
	}
	comnd1 = ft_split(argv[COMD1], ' ');
	if (!comnd1)
		exit(4);
	dup2(fd_in, 0);
	close(fd_in);
	dup2(connect[1], 1);
	close(connect[1]);
	exe(env, comnd1);
	perror("error command 1");
	exit(5);
}

void	second_command(int *connect, char **argv, char **env)
{
	int		fd_out;
	char	**comnd2;

	close(connect[1]);
	fd_out = open(argv[OUTFILE], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_out < 0)
	{
		perror("error output file");
		exit(7);
	}
	comnd2 = ft_split(argv[COMD2], ' ');
	if (!comnd2)
		exit(8);
	dup2(connect[0], 0);
	close(connect[0]);
	dup2(fd_out, 1);
	close(fd_out);
	exe(env, comnd2);
	perror("error command 2");
	exit(9);
}

// void	end(int *connect, int pid_1, int pid_2)
// {
// 	close(connect[1]);
// 	close(connect[0]);
// 	waitpid(pid_1, NULL, 0);
// 	waitpid(pid_2, NULL, 0);
// }

int	main(int argc, char **argv, char **env)
{
	pid_t	pid_1;
	int		connect[2];

	// pid_t	pid_2;
	if (argc != 5 || isspace_str(argv[2]) == 0 || isspace_str(argv[3]) == 0)
	{
		write(2, "wrong param\n", 12);
		exit(1);
	}
	pipe(connect);
	pid_1 = fork();
	if (pid_1 == -1)
		exit(2);
	if (pid_1 == 0)
		first_command(connect, argv, env);
	else
	{
		if (fork() == 0)
			second_command(connect, argv, env);
		close(connect[1]);
		close(connect[0]);
		waitpid(pid_1, NULL, 0);
		waitpid(-1, NULL, 0);
	}
}

// pid_2 = fork();
// if (pid_2 == -1)
// 	exit(6);
// if (pid_2 == 0)
// 	second_command(connect, argv, env);
// else
// 	end(connect, pid_1, pid_2);
