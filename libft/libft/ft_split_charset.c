/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 13:14:38 by jriga             #+#    #+#             */
/*   Updated: 2025/04/28 15:40:19 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

size_t	count_words(char *str, char *charset)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (!ft_ischarset(*str, charset))
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		str++;
	}
	return (count);
}

char	*split_nextword(char *str, char *charset)
{
	while (*str && !ft_ischarset(*str, charset))
		str++;
	while (*str && ft_ischarset(*str, charset))
		str++;
	return (str);
}

char	*ft_splitdup(char *src, char *charset)
{
	size_t	size;
	char	*str;
	size_t	i;

	size = 0;
	i = 0;
	while (src[size] && !ft_ischarset(src[size], charset))
		size++;
	str = (char *)malloc(size + 1);
	if (!str)
		return (NULL);
	while (i < size)
	{
		str[i] = src[i];
		i++;
	}
	str[size] = '\0';
	return (str);
}

char	**ft_split_charset(char *str, char *charset)
{
	size_t	i;
	size_t	totlen;
	char	**strs;

	totlen = count_words(str, charset);
	strs = (char **)malloc(sizeof(char *) * (totlen + 1));
	i = 0;
	if (!strs)
		return (NULL);
	while (*str && ft_ischarset(*str, charset))
		str++;
	while (i < totlen)
	{
		strs[i] = ft_splitdup(str, charset);
		str = split_nextword(str, charset);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}
