/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bytecode_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzarate <rzarate@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/23 14:10:59 by rzarate           #+#    #+#             */
/*   Updated: 2018/06/23 15:36:55 by rzarate          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

void	handle_reg_code(char *s, uint32_t *tmp, uint8_t *bytes)
{
	*tmp = ft_atoi(s);
	*bytes = REG_SIZE;
}

void	handle_ind_code(char *s, uint32_t *tmp, uint8_t *bytes)
{
	*tmp = ft_atoi(s);
	*bytes = IND_SIZE;
}

void	handle_dir_tmp(char *s, uint32_t *tmp,
						t_labels *labels, uint32_t bytes_so_far)
{
	if (s[1] == LABEL_CHAR)
	{
		*tmp = labels_search(labels, &s[2]);
		DBI(*tmp);
		if (*tmp <= bytes_so_far)
			*tmp = (0xFFFFFFFF - (bytes_so_far - *tmp - 1));
		else
			*tmp -= bytes_so_far;
		DBI(bytes_so_far);
		DBI(*tmp);
	}
	else
		*tmp = ft_atoi(&s[1]);
}
