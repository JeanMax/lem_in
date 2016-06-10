/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/10 18:14:35 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

# define LEM_IN_H

# include "libft.h"

/*
** error code enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_USAGE = (1 << 1),
	E_READ = (1 << 2),
	E_INVALID = (1 << 3),
};

/*
** room status enum
*/
enum					e_status
{
	START,
	END,
	EMPTY,
	FULL
};

/*
** room struct
*/
typedef struct s_room	t_room;
struct	s_room
{
	t_arr			*linked_rooms;
	char			*name;
	t_uint			x;
	t_uint			y;
	t_uint			distance;
	enum e_status	status;
};

/*
** BASE
** error.c
*/
void					error(t_uint flag, char *msg);

/*
** PARSER
** parse.c
*/
void					parse(t_arr *ants, t_arr *rooms);

/*
** DOER
** todo.c
*/

#endif
