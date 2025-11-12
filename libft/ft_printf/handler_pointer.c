/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_pointer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:06:11 by jriga             #+#    #+#             */
/*   Updated: 2025/05/01 14:40:50 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	handler_pointer(va_list *ap)
{
	void	*ptr;

	ptr = va_arg(*ap, void *);
	if (!ptr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	ft_putstr("0x");
	ft_putnbr_hex_ulong((unsigned long)ptr, 'x');
	return (ft_hexlen_l((unsigned long)ptr) + 2);
}
