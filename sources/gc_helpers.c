/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 17:17:28 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/08 14:55:56 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libgc.h"

size_t	gc_len(void)
{
	t_gc	*collector;

	collector = getgc();
	if (! collector)
		return (0);
	return (collector->len);
}

void	print_collector(void)
{
	t_gc	*collector;
	size_t	index;
	size_t	size;

	collector = getgc();
	if (! collector)
		return ;
	index = 0;
	size = collector->size;
	ft_dprintf(STDERR_FILENO, "Printing collector\n");
	while (index < size)
	{
		ft_dprintf(STDERR_FILENO, "This is the pointer #%u : %p\n", \
		index, *(collector->memzones + index));
		index ++;
	}
	ft_dprintf(STDERR_FILENO, "Collector Printed\n");
}

void	*wrap_pointer(void *ptr)
{
	if (! (ptr && gc_add(ptr)))
		return (ptr);
	free(ptr);
	return (NULL);
}
