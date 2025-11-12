/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 01:13:49 by jriga             #+#    #+#             */
/*   Updated: 2025/09/04 01:15:18 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	binary_search(int *tab, int size, int nb)
{
	int	low;
	int	high;
	int	mid;

	low = 0;
	high = size - 1;
	mid = (low + high) / 2;
	while (tab[mid] != nb)
	{
		if (low > high)
			return (-1);
		if (tab[mid] < nb)
			low = mid + 1;
		else
			high = mid - 1;
		mid = (low + high) / 2;
	}
	return (mid);
}
