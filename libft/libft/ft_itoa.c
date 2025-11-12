/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 10:13:24 by jriga             #+#    #+#             */
/*   Updated: 2025/06/09 21:29:35 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	num_len(int n)
{
	int	i;

	i = 0;
	if (n < 0 || n == 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*nb;
	size_t	i;
	int		sign;

	i = 0;
	sign = 1;
	nb = malloc(num_len(n) + 1);
	if (!nb)
		return (NULL);
	if (n < 0)
		sign = -1;
	else if (n == 0)
		nb[i++] = '0';
	while (n != 0)
	{
		nb[i++] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (sign < 0)
		nb[i++] = '-';
	nb[i] = '\0';
	ft_revstr(nb);
	return (nb);
}

/* #include <stdio.h> */
/* int main(void) */
/* { */
/* 	char *str = ft_itoa(0); */
/* 	printf("%s", str); */
/* } */
