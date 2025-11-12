/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_builtins.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 17:00:35 by jriga             #+#    #+#             */
/*   Updated: 2025/05/01 14:54:06 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_BUILTINS_H
# define P_BUILTINS_H
# define PRINT_CHRS "cspdiuxX%"
# define N_SPECS 9

# include <stdarg.h>
# include "libft.h"

int		handler_string(va_list *ap);
int		handler_base10(va_list *ap);
int		handler_unsigned(va_list *ap);
void	printf_init(int (*handler_func[])(va_list *ap), char *p_ask);
int		handler_upper_hex(va_list *ap);
int		handler_unsigned(va_list *ap);
int		handler_string(va_list *ap);
int		handler_pointer(va_list *ap);
int		handler_percent(va_list *ap);
int		handler_lower_hex(va_list *ap);
int		handler_chr(va_list *ap);
int		handler_base10(va_list *ap);
int		ft_printf(const char *str, ...);

#endif
