/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriga <jriga@student.s19.be>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 21:27:03 by jriga             #+#    #+#             */
/*   Updated: 2025/04/29 15:53:31 by jriga            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;
	t_list	*new;
	t_list	*tail;

	if (!lst || !f)
		return (NULL);
	head = NULL;
	while (lst)
	{
		new = ft_lstnew(f(lst->u_ctt.content));
		if (!new)
		{
			ft_lstclear(&head, del);
			return (NULL);
		}
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		lst = lst->next;
	}
	return (head);
}
