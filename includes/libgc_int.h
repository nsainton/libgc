/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgc_int.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsainton <nsainton@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:07:31 by nsainton          #+#    #+#             */
/*   Updated: 2023/05/08 13:14:16 by nsainton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGC_INT_H
# define LIBGC_INT_H
# include "libft.h"
# include <stdlib.h>
# define TRASH_SIZE 50

enum e_errors
{
	NO_ERROR,
	COLLECTOR_ALLOCATION_ERROR = 20,
	NO_COLLECTOR,
	COLLECTOR_OVERFLOW,
	NOT_IN_COLLECTOR,
	COLLECTOR_ADD_ERROR,
	GC_UNKNOWN_ERROR
};

struct	s_gc
{
	void	**memzones;
	size_t	len;
	size_t	size;
};

typedef struct s_gc	t_gc;
#endif
