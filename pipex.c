/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:09:52 by maleca            #+#    #+#             */
/*   Updated: 2025/08/30 22:22:05 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_path(char	**all_path, int i)
{
	if (all_path && all_path[i])
	{
		while (all_path[i])
		{
			free(all_path[i]);
			i++;
		}
		free(all_path);
	}
}

char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**all_path;
	char	*tmp;
	char	*ret;

	if (!env)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	i = 0;
	while (ft_strncmp(env[i], "PATH", 4))
		i++;
	all_path = ft_split(&env[i][4], ':');
	i = 0;
	while (all_path[i])
	{
		tmp = ft_strjoin(all_path[i], "/");
		ret = ft_strjoin(tmp, cmd);
		if (access(ret, F_OK | X_OK) == 0)
			return (free_path(all_path, i + 1), ret);
		free(ret);
		i++;
	}
	free_path(all_path, i + 1);
	return (NULL);
}

void	ft_exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !cmd[0])
	{
		perror("invalid command");
		exit(EXIT_FAILURE);
	}
	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	printf("%s\n", path);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_printf("cmd not found");
		free(s_cmd);
		free(path);
		exit(EXIT_FAILURE);
	}
}

void	ft_tipeu1(char **av, char **env, int pipefd[2])
{
	int		fd;

	close(pipefd[0]);
	fd = open(av[1], O_RDONLY, 0644);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	ft_exec(av[2], env);
}

void	ft_tipeu2(char **av, char **env, int pipefd[2])
{
	int		fd;

	close(pipefd[1]);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	ft_exec(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];
	int		pid;

	if (ac < 5)
		perror("too few arguments");
	if (ac > 5)
		perror("too many arguments");
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
		ft_tipeu1(av, env, pipefd);
	close(pipefd[0]);
	pid = fork();
	if (pid == 0)
		ft_tipeu2(av, env, pipefd);
	close(pipefd[1]);
	while (wait(NULL) > 0)
		;
}
