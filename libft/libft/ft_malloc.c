/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:06:47 by jriga             #+#    #+#             */
/*   Updated: 2025/07/24 01:33:56 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_malloc(size_t size)
{
	t_header	*hdr;

	hdr = malloc(sizeof(t_header) + size);
	if (!hdr)
		return (NULL);
	hdr->size = size;
	return ((void *)((char *)hdr + sizeof(t_header)));
}
