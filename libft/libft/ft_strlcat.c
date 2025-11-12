/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 17:53:14 by jriga             #+#    #+#             */
/*   Updated: 2025/04/01 15:16:55 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, unsigned int n)
{
	size_t	idest;
	size_t	src_len;
	size_t	i;

	if (!dest && n == 0)
		return (ft_strlen(src));
	i = 0;
	idest = ft_strlen(dest);
	src_len = ft_strlen(src);
	if (n <= idest)
		return (n + src_len);
	while (src[i] && (idest + i) < (n - 1))
	{
		dest[idest + i] = src[i];
		i++;
	}
	dest[idest + i] = '\0';
	return (idest + src_len);
}
