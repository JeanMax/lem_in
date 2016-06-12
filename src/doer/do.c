/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 10:49:12 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/12 10:50:47 by mcanal           ###   ########.fr       */
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

void			move_ants(t_room **ants)
{
	t_room	**swap;
	t_room	*to;
	t_bool	job_done;

	job_done = FALSE;
	while (!job_done)
	{
		job_done = TRUE;
		swap = ants;
		while (*swap)
		{
			if ((to = find_best_room((*swap)->linked_rooms->ptr, (*swap)->distance)))
			{
				print_move((int)(swap - ants) + 1, to->name);
				if ((*swap)->status != START)
					(*swap)->status = EMPTY;
				*swap = to;
				if (to->status != END)
					to->status = FULL;
			}
			if ((*swap)->status != END)
				job_done = FALSE;
			swap++;
		}
		ft_putendl("");
	}
}
