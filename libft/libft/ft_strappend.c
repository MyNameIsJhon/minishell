/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 01:34:42 by jriga             #+#    #+#             */
/*   Updated: 2025/07/24 01:34:43 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strappend(char *str, char *buf, char *nl)
{
	char	*temp;
	char	*newl;

	if (!str)
	{
		if (nl)
			newl = ft_substr(buf, 0, nl - buf + 1);
		else
			newl = ft_strdup(buf);
	}
	else
	{
		if (nl)
			temp = ft_substr(buf, 0, nl - buf + 1);
		else
			temp = ft_strdup(buf);
		newl = ft_strjoin(str, temp);
		free(str);
		free(temp);
	}
	return (newl);
}
