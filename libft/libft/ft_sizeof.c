/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sizeof.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:20:56 by jriga             #+#    #+#             */
/*   Updated: 2025/07/24 01:41:59 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

size_t	ft_sizeof(void *ptr)
{
	t_header	*hdr;

	if (!ptr)
		return (0);
	hdr = (t_header *)((char *)ptr - sizeof(t_header));
	return (hdr->size);
}
