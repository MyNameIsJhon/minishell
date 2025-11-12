/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 17:03:52 by jriga             #+#    #+#             */
/*   Updated: 2025/06/01 17:35:17 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include <stddef.h>

typedef struct s_vector
{
	void		*content;
	size_t		max;
	size_t		actual;
	int			size_type;
}			t_vector;

t_vector	*vec_strappend(t_vector *vec, char *str);
void		vec_strappend_char(t_vector *vec, char c);
t_vector	*vector_init(int size_type, size_t space);
void		vec_free(t_vector *vec);

#endif
