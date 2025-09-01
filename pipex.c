/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 16:09:52 by maleca            #+#    #+#             */
/*   Updated: 2025/09/01 20:28:26 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft.h"

void	exec_cmd(char *cmd, char **env);
void	hdl_error(char *err_msg);

static void	ft_tipeu1(char **av, char **env, int pipefd[2])
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

static void	ft_tipeu2(char **av, char **env, int pipefd[2])
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

	if (ac < 5)
		hdl_error("too few arguments\n");
	if (ac > 5)
		hdl_error("too many arguments\n");
	if (pipe(pipefd) == -1)
		hdl_error("pipe\n");
	pid = fork();
	if (pid == 0)
		ft_tipeu1(av, env, pipefd);
	pid = fork();
	if (pid == 0)
		ft_tipeu2(av, env, pipefd);
	close(pipefd[0]);
	close(pipefd[1]);
	while (wait(NULL) > 0)
		;
	return (0);
}
