/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 15:39:51 by maleca            #+#    #+#             */
/*   Updated: 2025/09/09 17:42:45 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H

# define PIPEX_H

# include "../lib/includes/libft.h"
# include "../lib/includes/get_next_line.h"
# include "../lib/includes/ft_fprintf.h"

void	exec_cmd(char *cmd, char **env);
void	hdl_error(char *err_msg, char *arg);
char	**get_path_list(char **env);
char	*get_path(char *cmd, char **env);
void	free_path_list(char	**path_list, int i);
void	exec_ult(int ac, char **av, char **env);

#endif