/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:12:49 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/12 14:49:25 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is the main...
*/

#include "lem_in.h"

char			*g_exec_name;

/*
// <--- debug
static void		debug_room(t_room *room)
{
	t_room	**links;

	ft_debugstr("name", room->name);
	ft_debugnbr("x", (int)room->x);
	ft_debugnbr("y", (int)room->y);
	ft_debugnbr("distance", (int)room->distance);
	switch (room->status)
	{
		case START:
			ft_debugstr("status", "START");
			break ;
		case END:
			ft_debugstr("status", "END");
			break ;
		case EMPTY:
			ft_debugstr("status", "EMPTY");
			break ;
		case FULL:
			ft_debugstr("status", "FULL");
			break ;
		default:
			ft_debugstr("status", "????");
	}
	links = room->linked_rooms->ptr;
	while (*links)
	{
		ft_debugstr("link", (*links)->name);
		links++;
	}
	ft_putendl("");
}

static void		debug_rooms(t_room **rooms, int index)
{
	if (!*rooms)
		return ;
	ft_debugnbr("ROOM ~ index", index);
	debug_room(*rooms);
	debug_rooms(rooms + 1, index + 1);
}

static void		debug_ant(t_room *ant)
{
	ft_debugstr("room-name", ant->name);
	switch (ant->status)
	{
		case START:
			ft_debugstr("room-status", "START");
			break;
		case END:
			ft_debugstr("room-status", "END");
			break;
		default:
			ft_debugstr("room-status", "SOMEWHERE");
	}
	ft_putendl("");
}

static void		debug_ants(t_room **ants, int index)
{
	if (!*ants)
		return ;
	ft_debugnbr("ANT ~ index", index);
	debug_ant(*ants);
	debug_ants(ants + 1, index + 1);
}
// debug --->
*/


int				main(int ac, char **av)
{
	t_arr	*ants;
	t_arr	*rooms;

	g_exec_name = *av;
	if (ac != 1)
		error(E_USAGE, NULL);
	ants = ft_arrnew(32, sizeof(t_room *));
	rooms = ft_arrnew(32, sizeof(t_room *));

	parse(ants, rooms);
	ft_putendl("");
	move_ants(ants->ptr);

	/* debug_rooms(rooms->ptr, 0);	/\* debug *\/ */
	/* debug_ants(ants->ptr, 0);	/\* debug *\/ */

	ft_arrdel(&rooms);
	ft_arrdel(&ants);
	return (EXIT_SUCCESS);
}
