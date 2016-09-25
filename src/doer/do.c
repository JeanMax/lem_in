/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 10:49:12 by mcanal            #+#    #+#             */
/*   Updated: 2016/09/25 19:32:57 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "doer.h"

static void		print_move(int ant_index, char *room_name)
{
	ft_putchar('L');
	ft_putnbr(ant_index);
	ft_putchar('-');
	ft_putstr(room_name);
	ft_putchar(' ');
}

static t_room	*find_best_room(t_room **rooms, t_uint distance)
{
	t_room *best;

	best = NULL;
	while (*rooms)
	{
		if (((*rooms)->status == EMPTY || (*rooms)->status == END) \
				&& (*rooms)->distance <= distance \
				&& (!best || (best->distance > (*rooms)->distance)))
			best = *rooms;
		rooms++;
	}
	return (best);
}

static t_bool	move_loop(t_room **ants)
{
	t_bool	job_done;
	t_room	*to;

	job_done = TRUE;
	while (*ants)
	{
		if ((to = find_best_room((*ants)->linked_rooms->ptr, \
								(*ants)->distance)))
		{
			print_move((int)(ants - ants) + 1, to->name);
			if ((*ants)->status != START)
				(*ants)->status = EMPTY;
			*ants = to;
			if (to->status != END)
				to->status = FULL;
		}
		if ((*ants)->status != END)
			job_done = FALSE;
		ants++;
	}
	ft_putendl("");
	return (job_done);
}

void			move_ants(t_room **ants)
{
	while (!move_loop(ants))
		;
}
