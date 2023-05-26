/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:17:10 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/26 13:08:10 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

int	allocate_tab(t_tab *tab, t_csizet size, t_csizet elemsize)
{
	void	*zones;

	zones = gcmalloc(size * elemsize);
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

	zones = gcrealloc(tab->tab, tab->size * tab->elemsize, newsize\
	* tab->elemsize);
	if (! zones)
		return (COLLECTOR_ALLOCATION_ERROR);
	tab->tab = zones;
	tab->size = newsize;
	return (COLLECTOR_NO_ERROR);
}
