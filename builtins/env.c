/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 01:53:28 by jriga             #+#    #+#             */
/*   Updated: 2025/11/24 00:23:12 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	**convert_env(t_env *env, t_arena *memory)
{
	int		len;
	int		i;
	int		y;
	char	**envc;
	int		entry_len;

	if (!env || !memory)
		return (NULL);
	len = env_len(env);
	envc = arena_alloc(memory, sizeof(char *) * (len + 1), sizeof(char *));
	i = 0;
	while (env)
	{
		entry_len = ft_strlen(env->name) + ft_strlen(env->value) + 2;
		envc[i] = arena_alloc(memory, entry_len * sizeof(char), sizeof(char *));
		y = ft_strlcpy(envc[i], env->name, entry_len);
		envc[i][y] = '=';
		envc[i][y + 1] = '\0';
		if (env->value)
			ft_strlcat(envc[i], env->value, entry_len);
		env = env->next;
		i++;
	}
	envc[i] = NULL;
	return (envc);
}

void	print_env(t_env *envs)
{
	t_env	*curs;

	curs = envs;
	while (curs)
	{
		if (curs->value)
			printf("%s=%s\n", curs->name, curs->value);
		else
			printf("%s=\n", curs->name);
		curs = curs->next;
	}
}
