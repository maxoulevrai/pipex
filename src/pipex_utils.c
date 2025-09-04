/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 22:26:59 by maleca            #+#    #+#             */
/*   Updated: 2025/09/04 19:04:59 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	hdl_error(char *err_msg)
{
	ft_printf("pipex: ");
	perror(err_msg);
	exit(EXIT_FAILURE);
}

void	free_path_list(char	**path_list, int i)
{
	if (path_list)
	{
		while (path_list[i])
			free(path_list[i++]);
		free(path_list);
	}
}

char	**get_path_list(char **env)
{
	char	**path_list;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (NULL);
	path_list = ft_split(&env[i][5], ':');
	if (!path_list)
		return (NULL);
	return (path_list);
}

char	*get_path(char *cmd, char **env)
{
	char	**path_list;
	char	*tmp;
	char	*ret;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path_list = get_path_list(env);
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		ret = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(ret, F_OK | X_OK) == 0)
			return (free_path_list(path_list, i + 1), ret);
		free(ret);
		i++;
	}
	return (free_path_list(path_list, 0), NULL);
}

void	exec_cmd(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	if (!cmd || !cmd[0])
		hdl_error("invalid command");
	s_cmd = ft_split(cmd, ' ');
	path = get_path(s_cmd[0], env);
	printf("%s\n", path);
	if (execve(path, s_cmd, env) == -1)
	{
		free_dtab(s_cmd);
		free(path);
		hdl_error("cmd not found");
	}
}
