/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 09:57:43 by jriga             #+#    #+#             */
/*   Updated: 2025/10/27 20:33:14 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>

static size_t	count_words(char *str, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c)
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

static char	*split_nextword(char *str, char c)
{
	while (*str && *str != c)
		str++;
	while (*str && *str == c)
		str++;
	return (str);
}

static char	*ft_splitdup(char *src, char c)
{
	size_t	size;
	char	*str;
	size_t	i;

	size = 0;
	i = 0;
	while (src[size] && src[size] != c)
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

char	**ft_split(const char *s, char c)
{
	size_t	i;
	size_t	totlen;
	char	**strs;

	if (!s)
		return (NULL);
	totlen = count_words((char *)s, c);
	strs = (char **)malloc(sizeof(char *) * (totlen + 1));
	i = 0;
	if (!strs)
		return (NULL);
	while (*s && *s == c)
		s++;
	while (i < totlen)
	{
		strs[i] = ft_splitdup((char *)s, c);
		s = split_nextword((char *)s, c);
		i++;
	}
	strs[i] = NULL;
	return (strs);
}

/* #include <stdio.h> */
/* int main(void) */
/* { */
/*     char **tab = ft_split("Salut mon amis comment tu vas", ' '); */
/*     for (int i = 0; tab[i]; i++) */
/*         printf("%s\n", tab[i]); */
/*     for (int i = 0; tab[i]; i++) */
/*         free(tab[i]); */
/*     free(tab); */
/* } */
