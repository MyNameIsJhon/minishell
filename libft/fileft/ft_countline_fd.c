/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countline_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 18:30:27 by jriga             #+#    #+#             */
/*   Updated: 2025/06/01 13:19:08 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#define CNT_BUFF 1024

size_t	ft_countline_fd(char *path)
{
	int		fd;
	char	buff[CNT_BUFF + 1];
	ssize_t	bytes;
	size_t	rows;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	rows = 0;
	bytes = read(fd, buff, CNT_BUFF);
	while (bytes > 0)
	{
		buff[bytes] = '\0';
		rows += ft_strcount_char(buff, '\n');
		bytes = read(fd, buff, CNT_BUFF);
	}
	close(fd);
	return (rows);
}
