/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:09:52 by maleca            #+#    #+#             */
/*   Updated: 2025/09/02 15:41:20 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_tipeu1(int ac, char **av, char **env, int pipefd[2], int i)
{
	int	fd;

	close(pipefd[0]);
	fd = open(av[1], O_RDONLY, 0644);
	if (fd == -1)
		hdl_error("issue with the infile");
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	exec_cmd(av[2], env);
}

static void	ft_tipeu2(int ac, char **av, char **env, int pipefd[2], int i)
{
	int	fd;

	close(pipefd[1]);
	fd = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		hdl_error("failed creating the outfile\n");
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(fd);
	exec_cmd(av[3], env);
}

int	main(int ac, char **av, char **env)
{
	int		pipefd[2];
	int		pid;
	int		i;

	if (ac < 5)
		hdl_error("too few arguments\n");
	if (ac > 5)
		hdl_error("too many arguments\n");
	if (pipe(pipefd) == -1)
		hdl_error("pipe\n");
	i = 1;
	while (i < ac - 1)
	{
		pid = fork();
		if (pid == 0)
			ft_tipeu1(ac, av, env, pipefd, i);
		pid = fork();
		if (pid == 0)
			ft_tipeu2(ac, av, env, pipefd, i);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	while (wait(NULL) > 0)
		;
	return (0);
}
