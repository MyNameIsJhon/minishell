/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_hex_ulong.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:31:33 by jriga             #+#    #+#             */
/*   Updated: 2025/04/28 16:59:49 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_hex_ulong(unsigned long long n, char format)
{
	if (n >= 16)
	{
		ft_putnbr_hex_ulong(n / 16, format);
		ft_putnbr_hex_ulong(n % 16, format);
	}
	else
	{
		if (n <= 9)
			ft_putchar('0' + n);
		else
		{
			if (format == 'x')
				ft_putchar('a' + (n - 10));
			else if (format == 'X')
				ft_putchar('A' + (n - 10));
		}
	}
}
