/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcanal <mcanal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/12 03:39:12 by mcanal            #+#    #+#             */
/*   Updated: 2016/06/09 17:47:12 by mcanal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** errors handling
** first arg is a flag including enums e_error (cf .h) (ex: E_OPEN | E_NOEXIT)
** second arg is an optionnal error message
*/

#include "lem_in.h"
#include <stdlib.h>

/*
** I'm pretty sure there is another way...
*/
static int		get_index(t_uint flag)
{
	int		index;

	index = 0;
	while ((flag /= 2))
		index++;
	return (index - 1);
}

void			error(t_uint flag, char *msg)
{
	const char	*error[] = {
		"Usage: ./lem-in", //TODO: save av[0] in global?
		"Ouch... can't read this.",
		"What the heck is that file? Nah, just try with something else. - "
	};

	if (msg)
	{
		fail(error[get_index(flag & (t_uint)~E_NOEXIT)]);
		failn(msg);
	}
	else
		failn(error[get_index(flag & (t_uint)~E_NOEXIT)]);
	if (!(flag & E_NOEXIT))
		exit(EXIT_FAILURE);
}
