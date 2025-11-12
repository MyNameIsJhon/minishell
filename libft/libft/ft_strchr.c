/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 18:13:24 by jriga             #+#    #+#             */
/*   Updated: 2025/04/01 15:27:46 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: finir la fonction
char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char) c)
			return ((char *)(s));
		s++;
	}
	if (*s == (char) c)
		return ((char *)s);
	return ((char *)(0));
}
