/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:50:24 by jriga             #+#    #+#             */
/*   Updated: 2025/05/01 15:16:42 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "libft.h"

int	handler_string(va_list *ap)
{
	char	*str;

	str = va_arg(*ap, char *);
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	else
		ft_putstr(str);
	return (ft_strlen(str));
}
