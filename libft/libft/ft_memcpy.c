/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:58:45 by jriga             #+#    #+#             */
/*   Updated: 2025/04/01 15:14:00 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	i = 0;
	if (!s1 && !s2)
		return (NULL);
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}

/* #include <stdio.h> */
/**/
/* int main(void) */
/* { */
/* 	char str[20]; */
/* 	char s2[] = "salut\0"; */
/* 	ft_memcpy((void *) str, s2, 5); */
/* 	printf("%s\n",str); */
/* 	return 0; */
/* } */
