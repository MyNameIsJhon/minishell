/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:16:03 by jriga             #+#    #+#             */
/*   Updated: 2025/07/24 01:32:48 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

void	ft_free(void *ptr)
{
	t_header	*hdr;

	if (!ptr)
		return ;
	hdr = (t_header *)ptr - 1;
	free(hdr);
}
