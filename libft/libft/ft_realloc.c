/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:27:52 by jriga             #+#    #+#             */
/*   Updated: 2025/07/24 01:41:31 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc(void *ptr, size_t size)
{
	unsigned char	*new;
	size_t			len;

	if (!ptr)
		return (ft_malloc(size));
	if (size == 0)
	{
		ft_free(ptr);
		return (NULL);
	}
	len = ft_sizeof(ptr);
	if (len == size)
		return (ptr);
	new = ft_malloc(size);
	if (!new)
		return (NULL);
	if (len > size)
		len = size;
	ft_memcpy(new, ptr, len);
	ft_free(ptr);
	return (new);
}
