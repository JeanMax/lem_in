/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 00:12:49 by mcanal            #+#    #+#             */
/*   Updated: 2016/09/25 19:08:17 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** this is the main...
*/

#include "lem_in.h"

char			*g_exec_name;

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
	ft_arrdel(&rooms);
	ft_arrdel(&ants);
	return (EXIT_SUCCESS);
}
