/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 21:10:42 by jriga             #+#    #+#             */
/*   Updated: 2025/08/16 11:53:52 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILEFT_H
# define FILEFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# ifndef FD_MAX
#  define FD_MAX 1024
# endif

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_countline_fd(char *path);
char	*get_file(char *path);

#endif
