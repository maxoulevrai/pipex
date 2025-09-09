/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 18:15:39 by maleca            #+#    #+#             */
/*   Updated: 2025/09/09 18:16:54 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	exec_ult(int ac, char **av, char **env)
{
	int	outfile;

	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile == -1)
			hdl_error("failed creating file: %s\n", av[ac - 1]);
	}
	else
	{
		outfile = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			hdl_error("failed creating file: %s\n", av[ac - 1]);
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	exec_cmd(av[ac - 2], env);
}
