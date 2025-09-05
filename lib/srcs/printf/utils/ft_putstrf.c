/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maleca <maleca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 04:02:59 by maleca            #+#    #+#             */
/*   Updated: 2025/09/05 17:50:16 by maleca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libft.h"

void	ft_putstrf(char *str, size_t *count)
{
	int	i;

	if (!str)
	{
		ft_putstrf("(null)", count);
		return ;
	}
	i = 0;
	while (str[i])
	{
		(*count)++;
		i++;
	}
	write(1, str, i);
}
