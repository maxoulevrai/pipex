/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:08:31 by maleca            #+#    #+#             */
/*   Updated: 2025/09/09 18:14:07 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	here_doc_child(int pipefd[2], char *LIMITER)
{
	char	*line;
	char	*limiter_nl;

	limiter_nl = ft_strjoin(LIMITER, "\n");
	close(pipefd[0]);
	line = get_next_line(STDIN_FILENO, limiter_nl);
	while (line)
	{
		if (ft_strcmp(line, limiter_nl) == 0)
		{
			close(pipefd[1]);
			free(limiter_nl);
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO, limiter_nl);
	}
	close(pipefd[1]);
	free(limiter_nl);
	free(line);
}

static void	hdl_here_doc(char *LIMITER, int ac)
{
	pid_t	pid;
	int		pipefd[2];

	if (ac < 6)
		hdl_error("too few arguments\n", NULL);
	if (pipe(pipefd) == -1)
		hdl_error("pipe() failed at hdl_here_doc()\n", NULL);
	pid = fork();
	if (pid == -1)
		hdl_error("fork() failed at hdl_here_doc()\n", NULL);
	if (pid == 0)
		here_doc_child(pipefd, LIMITER);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

static void	ft_tipeu(char *av, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		hdl_error("pipe() failed at ft_tipeu()\n", NULL);
	pid = fork();
	if (pid == -1)
		hdl_error("fork() failed at ft_tipeu()\n", NULL);
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		exec_cmd(av, env);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
}

static void	ult_cmd(int ac, char **av, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		hdl_error("fork() failed at ult_cmd()\n", NULL);
	if (pid == 0)
		exec_ult(ac, av, env);
	else
		wait(NULL);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	infile;

	if (ac < 5)
		hdl_error("too few arguments\n", NULL);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		hdl_here_doc(av[2], ac);
		i = 3;
	}
	else
	{
		i = 2;
		infile = open(av[1], O_RDONLY, 0644);
		if (infile == -1)
			ft_fprintf(STDERR_FILENO, "no such file or directory: %s\n", av[1]);
		dup2(infile, STDIN_FILENO);
		close(infile);
	}
	while (i < ac - 2)
		ft_tipeu(av[i++], env);
	ult_cmd(ac, av, env);
	return (0);
}
