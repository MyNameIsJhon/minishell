/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:07:52 by jriga             #+#    #+#             */
/*   Updated: 2025/04/01 15:15:29 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void	ft_revstr(char *tab)
{
	size_t	i;
	char	c;
	size_t	size;

	i = 0;
	c = 0;
	size = ft_strlen((char *)tab);
	while (i < (size / 2))
	{
		c = tab[size - i - 1];
		tab[size - i -1] = tab[i];
		tab[i] = c;
		i++;
	}
}
