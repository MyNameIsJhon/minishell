/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 23:22:50 by jriga             #+#    #+#             */
/*   Updated: 2025/05/01 15:49:39 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "p_builtins.h"
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <limits.h>

char	*ft_strchr_charset(char *str, char *charset)
{
	while (!ft_ischarset(*str, charset) && *str)
		str++;
	if (!*str)
		return (NULL);
	return (str);
}

int	print_next_to(char **str, char *charset)
{
	char	*cp;
	int		diff;

	if (!str || !charset || !*str)
		return (0);
	cp = ft_strchr_charset(*str, charset);
	if (!cp)
	{
		diff = ft_strlen(*str);
		write(1, *str, diff);
		*str += diff;
		return (diff);
	}
	diff = cp - *str;
	write(1, *str, diff);
	*str = cp;
	return (diff);
}

int	ft_printf(const char *str, ...)
{
	va_list		elements;
	int			(*handler_func[N_SPECS + 2])(va_list *ap);
	char		p_ask[N_SPECS + 2];
	char		*ptr;
	int			len;

	va_start(elements, str);
	printf_init(handler_func, p_ask);
	len = 0;
	while (*str)
	{
		len += print_next_to((char **)&str, "%");
		if (!str || !*str)
			break ;
		str++;
		ptr = ft_strchr(p_ask, *str);
		if (ptr)
		{
			len += handler_func[ptr - p_ask](&elements);
			str++;
		}
	}
	va_end(elements);
	return (len);
}

/* int main(void) */
/* { */
/* 	char	c = 'Z'; */
/* 	char	null_char = '\0'; */
/* 	char	*str = "42 is awesome"; */
/* 	char	*empty_str = ""; */
/* 	char	*null_str = NULL; */
/* 	int		neg_int = -214; */
/* 	int		pos_int = 214; */
/* 	int		zero = 0; */
/* 	unsigned int u_zero = 0; */
/* 	unsigned int u_large = UINT_MAX; */
/* 	void	*ptr = &c; */
/* 	void	*null_ptr = NULL; */
/* 	int		hex = 0xabcdef; */
/* 	int		hex_small = 0x1a; */
/* 	int		hex_zero = 0; */
/**/
/* 	// --- Test %c (char) --- */
/* 	ft_printf("[FT_PRINTF] Char simple : [%c]\n", c); */
/* 	ft_printf("[FT_PRINTF] Char nul : [%c]\n", null_char); */
/* 	ft_printf("[FT_PRINTF] Char '%' : [%c]\n", '%'); */
/* 	printf("[PRINTF]    Char simple : [%c]\n", c); */
/* 	printf("[PRINTF]    Char nul : [%c]\n", null_char); */
/* 	printf("[PRINTF]    Char '%%' : [%c]\n\n", '%'); */
/**/
/* 	// --- Test %s (string) --- */
/* 	ft_printf("[FT_PRINTF] String normal : [%s]\n", str); */
/* 	ft_printf("[FT_PRINTF] String vide : [%s]\n", empty_str); */
/* 	ft_printf("[FT_PRINTF] String NULL : [%s]\n", null_str); */
/* 	printf("[PRINTF]    String normal : [%s]\n", str); */
/* 	printf("[PRINTF]    String vide : [%s]\n", empty_str); */
/* 	printf("[PRINTF]    String NULL : [%s]\n\n", null_str); */
/**/
/* 	// --- Test %p (pointer) --- */
/* 	ft_printf("[FT_PRINTF] Pointer valide : [%p]\n", ptr); */
/* 	ft_printf("[FT_PRINTF] Pointer NULL : [%p]\n", null_ptr); */
/* 	ft_printf("[FT_PRINTF] Pointer sur string : [%p]\n", str); */
/* 	printf("[PRINTF]    Pointer valide : [%p]\n", ptr); */
/* 	printf("[PRINTF]    Pointer NULL : [%p]\n", null_ptr); */
/* 	printf("[PRINTF]    Pointer sur string : [%p]\n\n", str); */
/**/
/* 	// --- Test %d (decimal signed) --- */
/* 	ft_printf("[FT_PRINTF] Decimal positif : [%d]\n", pos_int); */
/* 	ft_printf("[FT_PRINTF] Decimal negatif : [%d]\n", neg_int); */
/* 	ft_printf("[FT_PRINTF] Decimal zero : [%d]\n", zero); */
/* 	printf("[PRINTF]    Decimal positif : [%d]\n", pos_int); */
/* 	printf("[PRINTF]    Decimal negatif : [%d]\n", neg_int); */
/* 	printf("[PRINTF]    Decimal zero : [%d]\n\n", zero); */
/**/
/* 	// --- Test %i (integer signed, même chose que d) --- */
/* 	ft_printf("[FT_PRINTF] Integer positif : [%i]\n", pos_int); */
/* 	ft_printf("[FT_PRINTF] Integer negatif : [%i]\n", neg_int); */
/* 	ft_printf("[FT_PRINTF] Integer zero : [%i]\n", zero); */
/* 	printf("[PRINTF]    Integer positif : [%i]\n", pos_int); */
/* 	printf("[PRINTF]    Integer negatif : [%i]\n", neg_int); */
/* 	printf("[PRINTF]    Integer zero : [%i]\n\n", zero); */
/**/
/* 	// --- Test %u (unsigned decimal) --- */
/* 	ft_printf("[FT_PRINTF] Unsigned zero : [%u]\n", u_zero); */
/* 	ft_printf("[FT_PRINTF] Unsigned normal : [%u]\n", 123456789); */
/* 	ft_printf("[FT_PRINTF] Unsigned UINT_MAX : [%u]\n", u_large); */
/* 	printf("[PRINTF]    Unsigned zero : [%u]\n", u_zero); */
/* 	printf("[PRINTF]    Unsigned normal : [%u]\n", 123456789); */
/* 	printf("[PRINTF]    Unsigned UINT_MAX : [%u]\n\n", u_large); */
/**/
/* 	// --- Test %x (hexadecimal lowercase) --- */
/* 	ft_printf("[FT_PRINTF] Hexadecimal normal : [%x]\n", hex); */
/* 	ft_printf("[FT_PRINTF] Hexadecimal petit : [%x]\n", hex_small); */
/* 	ft_printf("[FT_PRINTF] Hexadecimal zero : [%x]\n", hex_zero); */
/* 	printf("[PRINTF]    Hexadecimal normal : [%x]\n", hex); */
/* 	printf("[PRINTF]    Hexadecimal petit : [%x]\n", hex_small); */
/* 	printf("[PRINTF]    Hexadecimal zero : [%x]\n\n", hex_zero); */
/**/
/* 	// --- Test %X (hexadecimal uppercase) --- */
/* 	ft_printf("[FT_PRINTF] Hexadecimal normal (upper) : [%X]\n", hex); */
/* 	ft_printf("[FT_PRINTF] Hexadecimal petit (upper) : [%X]\n", hex_small); */
/* 	ft_printf("[FT_PRINTF] Hexadecimal zero (upper) : [%X]\n", hex_zero); */
/* 	printf("[PRINTF]    Hexadecimal normal (upper) : [%X]\n", hex); */
/* 	printf("[PRINTF]    Hexadecimal petit (upper) : [%X]\n", hex_small); */
/* 	printf("[PRINTF]    Hexadecimal zero (upper) : [%X]\n\n", hex_zero); */
/**/
/* 	// --- Test %% (literal %) --- */
/* 	ft_printf("[FT_PRINTF] Pourcentage seul : [%%]\n"); */
/* 	ft_printf("[FT_PRINTF] Double pourcentage : [%%%%]\n"); */
/* 	ft_printf("[FT_PRINTF] Texte et pourcentage : [ok%%ok]\n"); */
/* 	printf("[PRINTF]    Pourcentage seul : [%%]\n"); */
/* 	printf("[PRINTF]    Double pourcentage : [%%%%]\n"); */
/* 	printf("[PRINTF]    Texte et pourcentage : [ok%%ok]\n\n"); */
/**/
/* 	return (0); */
/* } */
