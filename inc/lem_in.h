/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 13:23:15 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/09 11:31:01 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H

/*
** define
*/
# define LEM_IN_H

/*
** include
*/
# include "libft.h"

/*
** enum
*/
enum					e_error
{
	E_NOERROR = 0,
	E_NOEXIT = (1 << 0),
	E_USAGE = (1 << 1),
	E_OPEN = (1 << 2),
	E_READ = (1 << 3),
	E_INVALID = (1 << 4),
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


/*
** DOER
** todo.c
*/

#endif
