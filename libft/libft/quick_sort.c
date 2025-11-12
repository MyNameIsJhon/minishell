/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:24:11 by jriga             #+#    #+#             */
/*   Updated: 2025/09/04 01:24:31 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	partition(int *tab, int low, int high)
{
	int	tmp;
	int	i;
	int	j;

	tmp = tab[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (tab[j] <= tmp)
		{
			i++;
			ft_swap(&tab[i], &tab[j]);
		}
		j++;
	}
	ft_swap(&tab[i + 1], &tab[high]);
	return (i + 1);
}

void	quick_sort(int *tab, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(tab, low, high);
		quick_sort(tab, low, pi - 1);
		quick_sort(tab, pi + 1, high);
	}
}
