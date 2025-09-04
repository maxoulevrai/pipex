/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:08:31 by maleca            #+#    #+#             */
/*   Updated: 2025/09/04 19:46:42 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	here_doc_child(int pipefd[2], char *LIMITER)
{
	char	*line;
	char	*limiter_nl;

	limiter_nl = ft_strjoin(LIMITER, "\n");
	close(pipefd[0]);
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (ft_strncmp(line, limiter_nl, ft_strlen(limiter_nl)) == 0)
		{
			free(limiter_nl);
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	free(limiter_nl);
	free(line);
}
static void	hdl_here_doc(char *LIMITER)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		hdl_error("pipe here_doc");
	pid = fork();
	if (pid == -1)
		hdl_error("fork here_doc");
	if (pid == 0)
		here_doc_child(pipefd, LIMITER);
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		wait(NULL);
	}
}

static void	ft_tipeu(char *av, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		hdl_error("reg pipe");
	pid = fork();
	if (pid == -1)
		hdl_error("reg fork");
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		exec_cmd(av, env);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	infile;
	int	outfile;
	
	if (ac < 5)
		hdl_error("too few arguments");
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		if (ac < 6)
			hdl_error("NOOOOOO");
		i = 3;
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		hdl_here_doc(av[2]);
	}
	else
	{
		i = 2;
		infile = open(av[1], O_RDONLY, 0644);
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(infile, STDIN_FILENO);
	}
	while (i < ac - 2)
		ft_tipeu(av[i++], env);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(av[ac - 2], env);
	close(outfile);
	close(infile);
}
