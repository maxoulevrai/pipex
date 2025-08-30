/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:26:59 by maleca            #+#    #+#             */
/*   Updated: 2025/08/30 22:31:36 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/libft.h"

static void	free_path(char	**all_path, int i)
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

static char	*get_path(char *cmd, char **env)
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
