/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:31:19 by jriga             #+#    #+#             */
/*   Updated: 2025/04/01 15:27:26 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	totlen;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	totlen = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	str = malloc(totlen + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, (char *)s1, totlen + 1);
	ft_strlcat(str, s2, totlen + 1);
	return (str);
}

/* #include <stdio.h> */
/* int main(void) */
/* { */
/* 	char *str; */
/**/
/* 	str = ft_strjoin("Salut les amis ", "comment allez vous?"); */
/* 	printf("%s", str); */
/* } */
