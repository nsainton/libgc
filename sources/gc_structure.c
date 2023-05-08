/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_structure.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 10:53:57 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/08 14:58:54 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

t_gc	*getgc(void)
{
	static t_gc	collector;

	if (collector.memzones)
		return (&collector);
	if (! TRASH_SIZE)
		return (NULL);
	collector.memzones = ft_calloc(TRASH_SIZE, sizeof * collector.memzones);
	if (! collector.memzones)
	{
		ft_bzero(&collector, sizeof collector);
		return (NULL);
	}
	collector.size = TRASH_SIZE;
	collector.len = 0;
	return (&collector);
}

int	gc_realloc(void)
{
	t_gc	*collector;
	void	**newzone;
	size_t	newsize;
	size_t	elemsize;

	collector = getgc();
	newsize = 2 * collector->size;
	if (newsize < collector->size)
		return (COLLECTOR_OVERFLOW);
	elemsize = sizeof * collector->memzones;
	newzone = ft_realloc(collector->memzones, \
	collector->size * elemsize, newsize * elemsize);
	if (! newzone)
		return (COLLECTOR_ALLOCATION_ERROR);
	ft_bzero(newzone + collector->size, collector->size * elemsize);
	collector->memzones = newzone;
	collector->size = newsize;
	return (COLLECTOR_NO_ERROR);
}
