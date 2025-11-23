/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 01:53:28 by jriga             #+#    #+#             */
/*   Updated: 2025/11/21 04:50:03 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena_allocator.h"
#include "libft.h"
#include "minishell.h"
#include <stdio.h>

t_env	*new_env(char *name, char *value, t_arena *memory)
{
	t_env	*env;

	env = arena_alloc(memory, sizeof(t_env), sizeof(t_env));
	if (!env)
		return (NULL);
	env->next = NULL;
	env->name = ar_strdup(name, memory);
	env->value = ar_strdup(value, memory);
	return (env);
}

void	env_add_back(t_env *env, t_env **envs)
{
	t_env	*curs;

	curs = *envs;
	while (curs->next)
		curs = curs->next;
	curs->next = env;
}

t_env	*find_env(char *name, t_env *envs)
{
	if (!name)
		return (NULL);
	while (envs)
	{
		if (!ft_strcmp(name, envs->name))
			return (envs);
		envs = envs->next;
	}
	return (NULL);
}

void	env_delete(char *name, t_env **envs)
{
	t_env	*curs;

	curs = *envs;
	if (!ft_strcmp(name, curs->name))
	{
		*envs = curs->next;
		return ;
	}
	while (curs && curs->next)
	{
		if (!ft_strcmp(curs->next->name, name))
		{
			curs->next = curs->next->next;
			break ;
		}
		curs = curs->next;
	}
}

t_env	*env_init(char **envp, t_arena *memory)
{
	t_env	*env;
	char	**curs;
	int		i;

	curs = ar_split(envp[0], '=', memory);
	env = new_env(curs[0], curs[1], memory);
	i = 0;
	while (envp[i])
	{
		curs = ar_split(envp[i], '=', memory);
		env_add_back(new_env(curs[0], curs[1], memory), &env);
		i++;
	}
	return (env);
}

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
		if (env->value)
			entry_len = ft_strlen(env->name) + ft_strlen(env->value) + 2;
		else
			entry_len = ft_strlen(env->name) + 2;
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
