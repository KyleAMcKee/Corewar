# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rzarate <rzarate@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/25 10:27:14 by bpierce           #+#    #+#              #
#    Updated: 2018/06/23 14:11:40 by rzarate          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

FILES = main \
		parse \
		tokenizer \
		token_type_verifiers \
		token_subtype_verifiers \
		tokenizer_helpers \
		op_handler_1 \
		op_handler_2 \
		op_handler_helpers \
		bytecode \
		bytecode_helpers \
		op_queue \
		label_hashtable \
		utility_1 \
		utility_2 \
		utility_3 \

C_FLAGS = -Wall -Wextra -Werror

C_LOC = src/
C_NAM = $(addsuffix .c, $(FILES))
C_SRC = $(addprefix $(C_LOC), $(C_NAM))

O_LOC = obj/
O_NAM = $(addsuffix .o, $(FILES))
O_SRC = $(addprefix $(O_LOC), $(O_NAM))

LIB_LOC = ../libft/
LIB_NAM = libft.a
LIB_SRC = $(addprefix $(LIB_LOC), $(LIB_NAM))

H_LOCS = -I inc -I ../libft/inc
HEADERS = inc/assembler.h

RED = [31m
GREEN = [32m
BLUE = [34m
YELLOW = [33m
MAGENTA = [35m
GREY = [37m
GREEN_LIGHT = [92m
YELLOW_LIGHT = [93m
YELLOW_BOLD = [1;33m
MAGENTA_LIGHT = [95m
BLINK = [5m
END_COLOUR = [0m

all: $(NAME)

$(NAME): $(LIB_SRC) $(O_SRC)
	@echo "$(YELLOW_BOLD)Compiling executable... $@$(END_COLOUR)"
	@gcc $(C_FLAGS) $^ -o $@
	@echo

$(O_LOC)%.o: $(C_LOC)%.c $(HEADERS)
	@mkdir -p $(O_LOC)
	@echo "$(GREY)Re-compiling src file... $(END_COLOUR)$(YELLOW)$<$(END_COLOUR)"
	@gcc $(C_FLAGS) $(H_LOCS) -o $@ -c $<

$(LIB_SRC): force
	@echo "$(YELLOW)----------- Checking Libft Library -----------$(END_COLOUR)"
	@printf "$(YELLOW_LIGHT)$@ re-compile status: $(END_COLOUR)"
	@make -C $(LIB_LOC)
	@echo "$(YELLOW)----------- Library Check Complete -----------$(END_COLOUR)"

force:
	@true

clean:
	@mkdir -p $(O_LOC)
	@/bin/rm -rf $(O_SRC)
	@make clean -C $(LIB_LOC)
	@echo "$(GREEN)clean complete!$(END_COLOUR)"

fclean: clean
	@/bin/rm -f $(NAME)
	@make fclean -C $(LIB_LOC)
	@echo "$(GREEN)fclean complete!$(END_COLOUR)"

re: fclean all

.PHONY: all force clean fclean re
