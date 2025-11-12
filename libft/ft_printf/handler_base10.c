/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_base10.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:52:21 by jriga             #+#    #+#             */
/*   Updated: 2025/04/29 09:45:28 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	handler_base10(va_list *ap)
{
	int	nb;

	nb = va_arg(*ap, int);
	ft_putnbr(nb);
	return (ft_nbrlen(nb));
}
