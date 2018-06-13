/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/02 13:45:23 by bpierce           #+#    #+#             */
/*   Updated: 2018/06/02 14:28:58 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    loop(t_corewar *core)
{
	uint8_t		board_value;
	t_process	*process;

	while (1)
	{
		while (!isemptys(&PROCESS_STACK[CURRENT_CYCLE]))
		{
			process = pop(&PROCESS_STACK[CURRENT_CYCLE]);
			process->instruct(core, process);
			board_value = ZERO_AT_BAD_INSTR(process->curr_pc->value);
			process->instruct = core->op[board_value].instruct;
			insert_process(core, &core->process_stack[(core->env.cycle + core->op[board_value].wait_time) % PROCESS_STACK_LEN], process);
		}
        ++core->env.cycle;
        if (!cycle_handle(core))
        	break ;
        key_hit();
        game_speed(GAME_SPEED); // 1 is fast, 50 is slow
	}
}

void    loop_viz(t_corewar *core)
{
	uint8_t		board_value;
	t_process	*process;

	while (1)
	{
		while (!isemptys(&PROCESS_STACK[CURRENT_CYCLE]))
		{
			process = pop(&PROCESS_STACK[CURRENT_CYCLE]);
			pop_process_cursor(core, process);
			print_process_info(&core->ncur, process);
			process->instruct(core, process);
			board_value = ZERO_AT_BAD_INSTR(process->curr_pc->value);
			process->instruct = core->op[board_value].instruct;
			insert_process(core, &core->process_stack[(core->env.cycle + core->op[board_value].wait_time) % PROCESS_STACK_LEN], process);
			wrefresh(core->ncur.playa[process->player->player_num - 1]);
		}
        ++core->env.cycle;
		print_game_info(core);
		wrefresh(core->ncur.bored);
		if (!cycle_handle(core))
			break ;
		// key_hit();
        game_speed(GAME_SPEED);
	}
}

uint8_t	cycle_handle(t_corewar *core)
{
	(void)core;
	return (1);
}

void    game_speed(uint8_t speed)
{
    int j = 0;

    while (j++ < ((speed * PROCESS_STACK_LEN * 10) << 3))
        for (int64_t d = 0; d < speed; d++){}
}