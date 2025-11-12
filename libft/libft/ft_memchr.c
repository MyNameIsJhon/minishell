/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:51:57 by jriga             #+#    #+#             */
/*   Updated: 2025/04/01 15:41:16 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*str;
	unsigned char		uc;

	i = 0;
	str = (const unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		if (str[i] == uc)
			return ((void *)(str + i));
		i++;
	}
	return (NULL);
}

/* #include <stdio.h> */
/* int main(void) */
/* { */
/* 	char hello[] = "salut mon amis"; */
/* 	printf("%s", (char*)ft_memchr((const void*) hello, (int) 't', 12)); */
/* } */
