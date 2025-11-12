/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freestrs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:20:17 by jriga             #+#    #+#             */
/*   Updated: 2025/04/28 17:09:20 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	freestrs(char **strs, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(strs[i]);
	free(strs);
}
