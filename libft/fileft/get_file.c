/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 15:07:19 by jriga             #+#    #+#             */
/*   Updated: 2025/07/24 02:37:37 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "fileft.h"
#include "libft.h"
#include "stdlib.h"
#include "vector.h"
#define FILE_BUFF 4096

static t_vector	*read_into_vector(int fd)
{
	char		buff[FILE_BUFF + 1];
	ssize_t		bytes;
	t_vector	*vec;

	vec = vector_init(sizeof(char), FILE_BUFF);
	if (!vec)
		return (NULL);
	bytes = read(fd, buff, FILE_BUFF);
	while (bytes > 0)
	{
		buff[bytes] = '\0';
		vec = vec_strappend(vec, buff);
		if (!vec)
			return (NULL);
		bytes = read(fd, buff, FILE_BUFF);
	}
	if (bytes < 0)
	{
		vec_free(vec);
		return (NULL);
	}
	return (vec);
}

char	*get_file(char *path)
{
	int			fd;
	t_vector	*vec;
	char		*file;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	vec = read_into_vector(fd);
	close(fd);
	if (!vec)
		return (NULL);
	file = ft_strdup((char *)vec->content);
	vec_free(vec);
	return (file);
}
