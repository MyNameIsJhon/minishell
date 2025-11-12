/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 20:54:10 by jriga             #+#    #+#             */
/*   Updated: 2025/04/01 15:48:11 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_ischarset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	if (start >= end)
		return (ft_strdup(""));
	while (end > start && ft_ischarset(s1[end - 1], set))
		end--;
	return (ft_substr(s1, start, end - start));
}

/* #include <stdio.h> */
/* int main(void) */
/* { */
/* 	char *str; */
/**/
/* 	str = ft_strtrim("     hello les amis *())))", "*() "); */
/* 	printf("%s", str); */
/* 	free(str); */
/* } */
