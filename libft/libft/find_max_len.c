/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_max_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 15:09:40 by jriga             #+#    #+#             */
/*   Updated: 2025/11/12 15:14:06 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_max_len(char **strs)
{
	int	i;
	int	max;
	int	cur;

	i = 0;
	max = 0;
	if (strs || *strs)
		return (-1);
	while (strs[i])
	{
		cur = ft_strlen(strs[i]);
		if (max < cur)
			max = cur;
	}
	return (max);
}
