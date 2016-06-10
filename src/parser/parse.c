/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 14:24:52 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/10 17:32:07 by mcanal           ###   ########.fr       */
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
	int		x;
	int		y;

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
	x = ft_atoi(line);
	while (*line && *line != ' ')
		line++;
	if (!*line)
		error(E_INVALID, "Weird room.");
	y = ft_atoi(++line);
	ft_arrpush(rooms, new_room(name, x, y, status), status == R_START ? 0 : -1);
}

static int		get_n_ants(char *line)
{
	int	n_ants;

	n_ants = ft_atoi(line);
	while (*line)
		if (!ft_isdigit(*line++))
			error(E_INVALID, "Invalid ants number.");
	if (n_ants < 1)
		error(E_INVALID, "Not enough ants.");
	return (n_ants);
}

static int		read_loop(t_arr *rooms, int n_ants, enum e_read status)
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
	else
	{
		fill_rooms(rooms, line, status);
		status = R_NONE;
	}
	ft_memdel((void **)&line);
	return (read_loop(rooms, n_ants, status));
}

void			parse(t_arr *ants, t_arr *rooms)
{
	int	n_ants;

	rooms->del = del_room;
	rooms->cmp = cmp_room_names;
	n_ants = read_loop(rooms, 0, R_NONE);
	ft_arrpush(ants, *((t_room **)ft_arrget(rooms, 0)), -1);
	ft_arrmult(ants, n_ants);
	ft_putendl("");
}
