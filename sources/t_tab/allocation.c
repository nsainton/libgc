/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:17:10 by nsainton          #+#    #+#             */
/*   Updated: 2023/06/01 16:13:53 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

int	allocate_tab(t_tab *tab, t_csizet size, t_csizet elemsize)
{
	void	*zones;

	zones = gccalloc(size, elemsize);
	if (! zones)
		return (COLLECTOR_ALLOCATION_ERROR);
	tab->tab = zones;
	tab->size = size;
	tab->elemsize = elemsize;
	tab->len = 0;
	return (COLLECTOR_NO_ERROR);
}

int	realloc_tab(t_tab *tab, t_csizet newsize)
{	
	void	*zones;
	size_t	size;
	size_t	esize;

	esize = tab->elemsize;
	size = tab->size;
	zones = gcrealloc(tab->tab, size * esize, newsize * esize);
	if (! zones)
		return (COLLECTOR_ALLOCATION_ERROR);
	tab->tab = zones;
	tab->size = newsize;
	ft_bzero(zones + tab->len * esize, (newsize - tab->len) * esize);
	return (COLLECTOR_NO_ERROR);
}
