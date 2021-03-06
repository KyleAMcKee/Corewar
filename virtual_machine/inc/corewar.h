/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:57:13 by bpierce           #+#    #+#             */
/*   Updated: 2018/06/23 12:54:32 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <sys/stat.h>
# include <ncurses.h>
# include "libft.h"
# include "op.h"

# define USE1 "usage: ./corewar champa.cor [b.cor c.cor d.cor]\n"
# define USE2 "Optional arguments:\n"
# define USE3 "-viz ... enables the visualizer to view the game\n"
# define USE4 "-dump number ...  ends game after [number] cycles and "
# define USE5 "dumps memory to the stdout\n"
# define USE6 "-n number champion ... select player number\n"
# define USE7 "-s number ... set the speed of the game\n"
# define USE8 "-a[ctivity] ... enables activity viewer in the visualizer\n"
# define USE9 "-r[ainbow] [optional speed 1 - 10] ... enable rainbow mode"
# define USAGE USE1 USE2 USE3 USE4 USE5 USE6 USE7 USE8 USE9

# define CSEM "Corewar Conflict:\n"

# define GAME_SPEED 0

# define MALL_ERR_MSG(a) ft_str256(2, "Failure to malloc: ", (a))
# define MALL_ERR(a, b) !(a) ? corewar_error(MALL_ERR_MSG(b), 1) : 1

# define PLAYA core->player[p_num - 1]
# define LAST_PLAYA core->env.last_player_to_call_live - 1

# define PLAYA_MUST_DIE core->player[i].last_live < last
# define PLAYA_NEEDS_TO_DIE	(!core->player[i].last_live || (PLAYA_MUST_DIE))
# define PLAYA_NEEDS_A_KILLING (!core->player[i].dead && (PLAYA_NEEDS_TO_DIE))

# define PROCESS_STACK_LEN 1024
# define PROCESS_STACK core->process_stack
# define PROCESS_STACK_P1 core->process_stack[3]
# define PROCESS_STACK_P2 core->process_stack[2]
# define PROCESS_STACK_P3 core->process_stack[1]
# define PROCESS_STACK_P4 core->process_stack[0]

# define CURRENT_CYCLE core->env.cycle % PROCESS_STACK_LEN

# define ZERO_AT_BAD_INSTR(a) ((a) < 17 ? (a) : 0)

# define REG process->reg

# define EB0 core->encoding_byte[0]
# define EB1 core->encoding_byte[1]
# define EB2 core->encoding_byte[2]

# define ARG0 core->args[0]
# define ARG00 core->args[0][0]
# define ARG01 core->args[0][1]
# define ARG02 core->args[0][2]
# define ARG03 core->args[0][3]

# define ARG1 core->args[1]
# define ARG10 core->args[1][0]
# define ARG11 core->args[1][1]
# define ARG12 core->args[1][2]
# define ARG13 core->args[1][3]

# define ARG2 core->args[2]
# define ARG20 core->args[2][0]
# define ARG21 core->args[2][1]
# define ARG22 core->args[2][2]
# define ARG23 core->args[2][3]

# define VIZ(a) core->flag.viz ? (a) : 0

# define RAINBOW_VALUE 6000
# define RAINBOW_TOP(a) (((a) < 5000) ? 1000 : (6000 - (a)))
# define RAINBOW_UP(a) ((a) < 3000 ? ((a) - 2000) : RAINBOW_TOP(a))
# define RAINBOW_CYCLE(a) ((a) < 2000 ? 0 : RAINBOW_UP(a))

struct s_corewar;
struct s_process;

enum
{
	P1 = 1,
	P2,
	P3,
	P4,
	P1B,
	P2B,
	P3B,
	P4B,
	INFOZ,
	DF,
	DF_BAR,
	ORANGE_STUFF,
	ORANGE_BAR,
};

enum
{
	REGISTER = 1,
	DIRECT,
	INDIRECT
};

/*
**	Flag structs
**	----------------------------------------------------------------------------
*/

typedef struct			s_flag_queue
{
	char				*flag;
	void				*flag_func;
}						t_flag_queue;

typedef struct			s_flag
{
	uint8_t				dump:1;
	uint8_t				viz:1;
	uint8_t				speed:1;
	uint8_t				rainbow:1;
	uint8_t				activity:1;
}						t_flag;

/*
**	Environment
**	----------------------------------------------------------------------------
*/

typedef struct			s_env
{
	uint32_t			cycle;
	uint32_t			cycle_counter;
	uint32_t			cycle_to_die;
	uint32_t			cycle_delta;
	uint32_t			nbr_live;
	uint32_t			total_lives;
	uint32_t			total_processes;
	uint32_t			max_checks;
	uint32_t			dump;
	uint32_t			last_cycle_when_live_was_called;
	uint8_t				last_player_to_call_live;
	uint8_t				num_players;
	uint8_t				game_speed;
	uint64_t			rainbow_red;
	uint64_t			rainbow_green;
	uint64_t			rainbow_blue;
	uint64_t			rainbow_speed;
	char				c_array[256][3];
}						t_env;

/*
**	Ncurses handling
*/

typedef struct			s_ncurses
{
	WINDOW				*bored;
	WINDOW				*bored_boreder;
	WINDOW				*playa[4];
	WINDOW				*infoz;
	WINDOW				*winwin;
}						t_ncurses;

/*
**	Core War structs
**	----------------------------------------------------------------------------
*/

typedef struct			s_player
{
	char				*filename;
	uint8_t				player_num;
	uint16_t			num_of_processes;
	uint32_t			last_live;
	uint32_t			num_live;
	uint16_t			instruction_size;
	uint8_t				dead;
	t_header			header;
}						t_player;

typedef struct			s_board_node
{
	uint8_t				value;
	uint16_t			index;
	struct s_board_node	*next;
	struct s_board_node	*prev;
	uint8_t				x;
	uint8_t				y;
	uint8_t				bored_color;
	t_stack				cursor_stack;
}						t_board_node;

typedef struct			s_operation
{
	void				(*instruct)(struct s_corewar *, struct s_process *);
	uint16_t			wait_time;
	char				name[6];
}						t_operation;

typedef struct			s_process
{
	t_player			*player;
	t_board_node		*curr_pc;
	uint32_t			id;
	uint32_t			last_live;
	uint8_t				carry;
	uint8_t				reg[REG_NUMBER + 1][REG_SIZE];
	t_operation			*op;
}						t_process;

typedef struct			s_corewar
{
	t_env				env;
	t_flag				flag;
	t_queue				flag_queue;
	t_board_node		*board;
	t_board_node		*node_addresses[MEM_SIZE];
	t_board_node		*node_addresses_rev[MEM_SIZE];
	t_stack				process_stack[PROCESS_STACK_LEN];
	t_player			player[MAX_PLAYERS];
	char				*playerfiles[MAX_PLAYERS + 1];
	uint8_t				encoding_byte[3];
	uint8_t				args[3][4];
	uint8_t				(*parse_arg[4])(struct s_corewar *, t_process *,
							uint8_t, uint8_t);
	t_operation			op[18];
	t_ncurses			ncur;
}						t_corewar;

/*
**	Error functions
*/

void					corewar_error(char *message, int return_value);
void					debug(char *message);

/*
**	Flag handling
*/

void					init_flag_queue(t_queue *q);
void					add_flag(t_queue *q, char *flag, void *flag_func);
unsigned int			flag_handler(t_corewar *c, char ***av);
void					*search_flag_queue(t_node *n, char *flag);
void					clean_flag_queue(t_queue *q);
void					dump_board(t_corewar *core);
/*
**	Initializing data
*/

void					init_environment(t_corewar *core);
void					init_parse_args(t_corewar *core);
void					init_character_array(t_corewar *core);

void					retrieve_data(t_corewar *core, char **argv);
unsigned int			flag_dump(t_corewar *core, char ***argv);
unsigned int			flag_n(t_corewar *core, char ***argv);
unsigned int			flag_viz(t_corewar *core, char ***argv);
unsigned int			flag_speed(t_corewar *core, char ***argv);
unsigned int			add_player_file(t_corewar *core, char *filename);
uint64_t				get_max_cycles(uint64_t init);
void					init_board(t_corewar *core);
void					create_board(t_board_node **brd,
							t_board_node **add, t_board_node **rev);

void					init_operations(t_operation *op);
void					init_wait_times(t_operation *op);
void					init_instruction_names(t_operation *op);

/*
**	NCurses Functionality
*/

void					init_ncurses(t_corewar *core);
void					init_ncurses_colors(void);
void					init_ncurses_character_array(t_corewar *core);
void					init_ncurses_bored(t_corewar *core);
void					init_ncurses_playa(t_corewar *core);
void					create_playa_window(WINDOW *win, t_player *p);
void					init_ncurses_infoz(t_corewar *core);

int						key_hit(t_corewar *core);
void					terminate_ncurses(t_corewar *core);

void					draw_to_bored(t_corewar *core,
							uint8_t player_num, uint16_t idx, uint8_t len);

void					print_player_info(t_ncurses *n, t_process *p);
void					print_game_info(t_corewar *core);

/*
**	Players
*/

void					add_new_player(t_corewar *core, char *f, uint8_t p_num);
size_t					import_player_file(char *filename, uint8_t **contents);
void					parse_player_name(t_player *p, uint8_t *contents);
void					parse_player_comment(t_player *p, uint8_t *contents);
void					init_player_processes(t_corewar *core);

/*
**	Processes
*/

t_process				*new_process(t_corewar *core,
							t_player *p, t_board_node *b, t_process *cpy);
void					insert_process(t_corewar *c, t_stack *s, t_process *p);

void					push_process_cursor(t_corewar *c, t_process *process);
void					pop_process_cursor(t_corewar *core, t_process *process);
void					draw_cursor(t_corewar *core, t_board_node *board);

/*
** Instructions
*/
void					first_(t_corewar *core, t_process *process);
void					bad_(t_corewar *core, t_process *process);

void					live_(t_corewar *core, t_process *process);
void					exec_live(uint32_t args, t_process *p, t_env *env);

void					ld_(t_corewar *core, t_process *process);

void					st_(t_corewar *core, t_process *process);

void					add_(t_corewar *core, t_process *process);

void					sub_(t_corewar *core, t_process *process);

void					and_(t_corewar *core, t_process *process);
uint32_t				get_and_args(t_corewar *c, t_process *process,
							uint16_t index, uint8_t arg_num);

void					or_(t_corewar *core, t_process *process);
uint32_t				get_or_args(t_corewar *c, t_process *process,
							uint16_t index, uint8_t arg_num);

void					xor_(t_corewar *core, t_process *process);
uint32_t				get_xor_args(t_corewar *c, t_process *process,
							uint16_t index, uint8_t arg_num);

void					zjmp_(t_corewar *core, t_process *process);

void					ldi_(t_corewar *core, t_process *process);
uint32_t				ldi_a_index(t_corewar *core, t_process *process,
							uint16_t index);
uint32_t				ldi_b_index(t_corewar *core, t_process *process);
void					do_ldi(t_corewar *core, t_process *process,
							uint32_t idx_res, uint16_t idx);

void					sti_(t_corewar *core, t_process *process);
uint32_t				sti_a_index(t_corewar *core, t_process *process,
							uint16_t index);
uint32_t				sti_b_index(t_corewar *core, t_process *process);

void					fork_(t_corewar *core, t_process *process);

void					lld_(t_corewar *core, t_process *process);

void					lldi_(t_corewar *core, t_process *process);
uint32_t				lldi_a_index(t_corewar *core, t_process *process,
							uint16_t index);
uint32_t				lldi_b_index(t_corewar *core, t_process *process);
void					do_lldi(t_corewar *core, t_process *process,
							uint32_t idx_res, uint16_t idx);

void					lfork_(t_corewar *core, t_process *process);

void					aff_(t_corewar *core, t_process *process);

/*
**	Loop and Stack
*/

void					loop(t_corewar *core);
void					loop_viz(t_corewar *core);
void					game_speed(uint8_t speed);

/*
**	Index
*/

uint16_t				get_index_unchained(uint16_t pc, uint8_t idx_byte1,
							uint8_t idx_byte2);
uint16_t				get_index(uint16_t pc, uint8_t idx_byte1,
							uint8_t idx_byte2);

/*
** Write, Read, Parse Bytes
*/

void					write_number_to_board(t_board_node *brd, uint8_t *num);
void					write_board_to_register(uint8_t *reg, t_board_node *b);
void					write_number_to_register(uint8_t *reg, uint32_t nbr);
void					write_reg_to_reg(uint8_t *dst_reg, uint8_t *src_reg);

uint32_t				read_from_board(t_board_node *board, uint8_t bytes);

uint8_t					parse_encoding_byte(t_corewar *c, t_process *process);

uint8_t					parse_arguments(t_corewar *core, t_process *process,
							uint8_t two_bytes);
uint8_t					parse_nothing(t_corewar *core, t_process *process,
							uint8_t i, uint8_t two_bytes);
uint8_t					parse_register(t_corewar *core, t_process *process,
							uint8_t i, uint8_t two_bytes);
uint8_t					parse_direct(t_corewar *core, t_process *process,
							uint8_t i, uint8_t two_bytes);
uint8_t					parse_indirect(t_corewar *core, t_process *process,
							uint8_t i, uint8_t two_bytes);

void					move_pc_by_encoding_byte(t_corewar *core,
							t_process *p, uint8_t read_two_bytes, uint8_t args);
uint32_t				smash_bytes(uint8_t *reg);
uint8_t					*unsmash_bytes(uint32_t nbr);

/*
**	Cycle checker
*/

uint8_t					cycle_handle(t_corewar *core);
uint8_t					terminate_players(t_corewar *core);
void					terminate_processes(t_corewar *core,
							t_stack *stk, uint32_t last);
void					terminate_process(t_corewar *core, t_stack *stk);

/*
**	Game Over
*/

uint8_t					game_over(t_corewar *core);
void					declare_winner(t_corewar *core);

/*
**	Bonus
*/

void					rainbow(t_corewar *core);
unsigned int			flag_rainbow(t_corewar *core, char ***argv);

void					activity(t_corewar *core);
unsigned int			flag_activity(t_corewar *core, char ***argv);

#endif
