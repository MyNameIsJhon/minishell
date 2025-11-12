/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 12:18:32 by jriga             #+#    #+#             */
/*   Updated: 2025/08/16 12:29:02 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	count_params(char *params)
{
	int	i;
	int	space;

	i = 0;
	space = 1;
	while (*params)
	{
		if (space && *params != ' ')
		{
			i++;
			space = 0;
		}
		else if (*params == ' ')
			space = 1;
		params++;
	}
	return (i);
}
