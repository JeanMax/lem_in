/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 16:22:06 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/10 18:15:56 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "parser.h"

t_room		*new_room(char *name, t_uint x, t_uint y, enum e_read status)
{
	t_room	*new;

	new = (t_room *)ft_memalloc(sizeof(t_room));
	new->name = ft_strdup(name);
	new->x = x;
	new->y = y;
	new->distance = UINT_MAX;
	if (status == R_START)
		new->status = START;
	else if (status == R_END)
		new->status = END;
	else
		new->status = EMPTY;
	new->linked_rooms = ft_arrnew(8, sizeof(t_room *));
	return (new);
}

void		del_room(void *room, size_t useless)
{
	(void)useless;
	ft_arrdel(&(*(t_room **)room)->linked_rooms);
	ft_memdel((void **)&(*(t_room **)room)->name);
	ft_memdel((void **)room);
}

int			cmp_room_names(const void *a, const void *b, size_t useless)
{
	(void)useless;
	return (ft_strcmp((char *)(*(t_room **)a)->name, *(char **)b));
}
