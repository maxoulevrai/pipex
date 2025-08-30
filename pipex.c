/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:09:52 by maleca            #+#    #+#             */
/*   Updated: 2025/08/30 22:31:35 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft.h"

void	ft_exec(char *cmd, char **env);

static void	ft_tipeu1(char **av, char **env, int pipefd[2])
{
	int	fd;

	close(pipefd[0]);
	fd = open(av[1], O_RDONLY, 0644);
	if (fd == -1)
		return ;
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	ft_exec(av[2], env);
}

static void	ft_tipeu2(char **av, char **env, int pipefd[2])
{
	int	fd;

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
