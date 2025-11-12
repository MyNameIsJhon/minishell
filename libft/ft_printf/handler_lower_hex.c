/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lower_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:03:10 by jriga             #+#    #+#             */
/*   Updated: 2025/05/01 15:50:04 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	handler_lower_hex(va_list *ap)
{
	unsigned int	nb;

	nb = va_arg(*ap, unsigned int);
	ft_putnbr_hex(nb, 'x');
	return (ft_hexlen(nb));
}
