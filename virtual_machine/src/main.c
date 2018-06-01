/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:57:13 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/31 12:54:46 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char **argv)
{
	t_corewar	core;

	if (argc == 1)
		corewar_error(USAGE, 1);
	ft_bzero(&core, sizeof(t_corewar));
	retrieve_data(&core, ++argv);
	init_player_processes(&core);
	int i = 0;
	while (i < 4)
	{
		ft_pflite("player: %u, name: %s\n", i + 1, core.player[i].header.prog_name);
		ft_pflite("player: %u, comm: %s\n", i + 1, core.player[i].header.comment);
		i++;
	}
	i = 0;
	while (i < MEM_SIZE)
	{
		printf("%0.2x", core.board[i]);
		printf(" ");
		if (!(i % 35) && i > 34)
			printf("\n");
		i++;
	}
//	validation();
//	ft_memcpy
	return (0);
}
