/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:39:51 by maleca            #+#    #+#             */
/*   Updated: 2025/09/02 17:05:40 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../lib/libft.h"

void	exec_cmd(char *cmd, char **env);
void	hdl_error(char *err_msg);
char	*get_path_list(char *cmd, char **env);
void	free_path_list(char	**path_list, int i);

#endif