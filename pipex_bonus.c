/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:08:31 by maleca            #+#    #+#             */
/*   Updated: 2025/09/02 15:59:51 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	hdl_here_doc(char *LIMITER)
{

}

static void	ft_tipeu(char *av, char **env)
{
	pid_t	pid;
	int		pipefd[2];

	if (pipe(pipefd) == -1)
		hdl_error("pipe");
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		exec(av, env);
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
		i = 3;
		outfile = open(av[ac - 2], O_WRONLY, O_APPEND, O_CREAT, 0777);
		hdl_here_doc(av[2]);
	}
	else
	{
		i = 2;
		infile = open(av[1], O_WRONLY, 0777);
		outfile = open(av[ac - 2], O_WRONLY, O_TRUNC, O_CREAT, 0777);
		dup2(infile, STDIN_FILENO);
	}
	while (i < ac - 2)
		ft_tipeu(av[i], env);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(av[ac - 2], env);
}
