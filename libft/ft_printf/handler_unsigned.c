/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_unsigned.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:00:19 by jriga             #+#    #+#             */
/*   Updated: 2025/04/30 15:13:29 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	handler_unsigned(va_list *ap)
{
	unsigned int	nb;

	nb = va_arg(*ap, unsigned int);
	ft_putnbr_unsigned(nb);
	return (ft_nbrlen_u(nb));
}
