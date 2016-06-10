/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <zboub@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/14 18:21:04 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/10 16:28:33 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H

# define PARSER_H

# include "lem_in.h"

/*
** read status enum
*/
enum					e_read
{
	R_NONE,
	R_START,
	R_END,
	R_LINKS
};

/*
** room.c
*/
t_room		*new_room(char *name, size_t x, size_t y, enum e_read status);
void		del_room(void *room, size_t useless);
int			cmp_room_names(const void *a, const void *b, size_t n);

#endif
