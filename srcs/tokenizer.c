/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 00:00:12 by jriga             #+#    #+#             */
/*   Updated: 2025/11/17 20:32:28 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>


t_token	*tokenize(char *input, t_arena *memory)
{
	t_token	*head;
	t_token	*tail;
	int		i;

	head = NULL;
	tail = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (!input[i])
			break ;
		if (input[i] == '\'' || input[i] == '"')
			i = extract_quoted(input, i, &head, &tail, memory);
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>')
			i = handle_operator(input, i, &head, &tail, memory);
		else
			i = extract_word(input, i, &head, &tail, memory);
	}
	return (head);
}
