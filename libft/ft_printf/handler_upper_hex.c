/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_upper_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:05:06 by jriga             #+#    #+#             */
/*   Updated: 2025/04/30 15:14:30 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	handler_upper_hex(va_list *ap)
{
	unsigned int	nb;

	nb = va_arg(*ap, unsigned int);
	ft_putnbr_hex(nb, 'X');
	return (ft_hexlen(nb));
}
