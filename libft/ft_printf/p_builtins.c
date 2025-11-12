/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_builtins.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 15:59:47 by jriga             #+#    #+#             */
/*   Updated: 2025/05/01 15:50:24 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "p_builtins.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>

void	printf_init(int (*handler_func[])(va_list *ap), char *p_ask)
{
	handler_func[0] = handler_chr;
	handler_func[1] = handler_string;
	handler_func[2] = handler_pointer;
	handler_func[3] = handler_base10;
	handler_func[4] = handler_base10;
	handler_func[5] = handler_unsigned;
	handler_func[6] = handler_lower_hex;
	handler_func[7] = handler_upper_hex;
	handler_func[8] = handler_percent;
	handler_func[9] = NULL;
	ft_strlcpy(p_ask, PRINT_CHRS, N_SPECS + 1);
}
