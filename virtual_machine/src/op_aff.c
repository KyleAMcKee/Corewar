/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:44:22 by bpierce           #+#    #+#             */
/*   Updated: 2018/06/02 14:56:22 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	0x10 - AFF...?
**	- - - - - - - - - -
**	Displays a character on the standard output % 256
**
**	Takes a parameter encoding byte
*/

void		aff_(t_corewar *core, t_process *process)
{
	(void)core;
	
	if (!(parse_encoding_byte(process)))
		return ;
	if (EB0 != REGISTER || EB1 || EB2)
		return ;
	if (!parse_arguments(process))
		return ;
	ft_putchar((int)smash_bytes(process->args[0]) % 256);	
	
}
