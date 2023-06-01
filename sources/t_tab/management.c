/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:24:39 by nsainton          #+#    #+#             */
/*   Updated: 2023/06/01 16:07:43 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

int	add_tab(t_tab *tab, void *elem)
{
	if (tab->len >= tab->size - 1 && realloc_tab(tab, 2 * tab->size))
		return (COLLECTOR_ALLOCATION_ERROR);
	ft_memcpy(tab->tab + tab->len * tab->elemsize, elem, tab->elemsize);
	tab->len ++;
	return (COLLECTOR_NO_ERROR);
}

void	delelem_tab(t_tab *tab, void (*del)(void *))
{
	if (! tab->len)
		return ;
	if (del)
		del(tab->tab + tab->len * tab->elemsize);
	tab->len --;
}

void	del_tab(t_tab *tab)
{
	free_node(tab->tab);
	ft_bzero(tab, sizeof * tab);
}
