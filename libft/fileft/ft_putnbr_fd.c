/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:37:10 by jriga             #+#    #+#             */
/*   Updated: 2025/05/30 21:15:05 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fileft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	long	un;

	un = nb;
	if (un < 0)
	{
		ft_putchar_fd('-', fd);
		un = -un;
	}
	if (un > 9)
		ft_putnbr_fd(un / 10, fd);
	ft_putchar_fd((un % 10) + '0', fd);
}
