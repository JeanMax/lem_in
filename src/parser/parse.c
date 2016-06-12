/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/12 13:08:24 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** todo
*/

#include "parser.h"

static void		link_rooms(t_arr *rooms, char *line)
{
	char	*to;
	t_room	*to_room;
	t_room	*from_room;

	if (!ft_strchr(line, '-'))
		error(E_INVALID, "Weird room linking.");
	to = line;
	while (*to && *to != '-')
		to++;
	*to++ = 0;
	if (!ft_strcmp(line, to))
		error(E_INVALID, "Can't link a room with itself.");
	from_room = ft_arrfind(rooms, line);
	to_room = ft_arrfind(rooms, to);
	if (!from_room || !to_room)
		error(E_INVALID, "Room not found (linking).");
	ft_arrpush(from_room->linked_rooms, to_room, -1);
	ft_arrpush(to_room->linked_rooms, from_room, -1);
}

static void		fill_rooms(t_arr *rooms, char *line, enum e_read status)
{
	char	*name;
	t_uint		x;
	t_uint		y;

	if (!ft_strchr(line, ' '))
	{
		link_rooms(rooms, line);
		return ;
	}
	name = line;
	while (*line && *line != ' ')
		line++;
	if (!*line)
		error(E_INVALID, "Weird room.");
	*line++ = 0;
	x = (t_uint)ft_atoi(line);
	while (*line && *line != ' ')
		line++;
	if (!*line)
		error(E_INVALID, "Weird room.");
	y = (t_uint)ft_atoi(++line);
	ft_arrpush(rooms, new_room(name, x, y, status), status == R_START ? 0 : -1);
}

static t_uint	get_n_ants(char *line)
{
	int	n_ants;

	if (ft_istoobig(line))
		error(E_INVALID, "Too many ants.");
	n_ants = ft_atoi(line);
	while (*line)
		if (!ft_isdigit(*line++))
			error(E_INVALID, "Invalid ants number.");
	if (n_ants < 1)
		error(E_INVALID, "Not enough ants.");
	return ((t_uint)n_ants);
}

static t_uint	read_loop(t_arr *rooms, t_uint n_ants, enum e_read status)
{
	char			*line;
	int				ret;

	line = NULL;
	if (!(ret = get_next_line(STDIN_FILENO, &line)))
		return (n_ants);
	else if (ret == -1)
		error(E_READ, NULL);
	ft_putendl(line);
	if (!n_ants)
		n_ants = get_n_ants(line);
	else if (*line == '#')
	{
		if (!ft_strcmp(line + 1, "#start"))
			status = R_START;
		else if (!ft_strcmp(line + 1, "#end"))
			status = R_END;
	}
	else if (*line && *line != 'L')
	{
		fill_rooms(rooms, line, status);
		status = R_NONE;
	}
	ft_memdel((void **)&line);
	return (read_loop(rooms, n_ants, status));
}

void			parse(t_arr *ants, t_arr *rooms)
{
	t_uint	n_ants;
	t_room	**start;

	rooms->del = del_room;
	rooms->cmp = cmp_room_names;
	n_ants = read_loop(rooms, 0, R_NONE);
	if (!(start = (t_room **)ft_arrget(rooms, 0)) \
			|| (*start)->status != START)
		error(E_INVALID, "Start-room not found.");
	ft_arrpush(ants, *start, -1);
	ft_arrmult(ants, n_ants);
	start = rooms->ptr;
	while (*start)
	{
		if ((*start)->status == END)
		{
			set_room_distances(*start, 0);
			/* ft_arrswap(rooms, -1, (int)(start - (t_room **)rooms->ptr)); */
			if ((*(t_room **)rooms->ptr)->distance == UINT_MAX)
				error(E_INVALID, "Start and End rooms not connected.");
			return ;
		}
		start++;
	}
	error(E_INVALID, "End-room not found.");
}
