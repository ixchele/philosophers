GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
CLEAR		= \033[K\r
NAME		= philo_bonus
CC			= cc
CFLAGS		= -Wall -Wextra -Werror #-g3
FLAGS		= -pthread -fsanitize=thread -g3
AR			= ar rcs
INCLUDES	= -I./headers/
# LIBFT_DIR	= libft
# LIBFT		= $(addprefix $(LIBFT_DIR)/, libft.a)
SRC			= src/main.c \
			  src/parse_and_init/parse_args.c \
			  src/parse_and_init/init_all.c \
			  src/run_simulation/start_simulation.c \
			  src/run_simulation/middle_man_routine.c \
			  src/utils/access_functions.c \
			  src/utils/philos_actions.c \
			  src/utils/utils_1.c \
			  src/utils/utils_2.c \
			  src/utils/utils_3.c \
			  src/utils/ft_itoa.c \
			  src/utils/ft_strdup.c \
			  src/utils/ft_strjoin.c
OBJ			= $(patsubst src/%.c, obj/%.o, $(SRC))
all: $(NAME)
	@echo "$(GREEN)$(BOLD)$(NAME) done!$(RESET)"

$(NAME): $(OBJ) #$(LIBFT) 
	@echo "$(CLEAR)$(YELLOW)linking $(NAME)...$(RESET)"
	@$(CC) $(OBJ) -o $(NAME) $(FLAGS) #$(LIBFT) 

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@echo -n "$(YELLOW)complining $@...$(RESET)$(CLEAR)"
	@$(CC) -c $(CFLAGS) $< $(INCLUDES) -o $@ $(FLAGS)

# $(LIBFT):
# 	@make -C $(LIBFT_DIR)/ all

clean:
	# @make -C $(LIBFT_DIR)/ clean
	@rm -rf obj

fclean: clean
	# @make -C $(LIBFT_DIR)/ fclean
	@rm -f $(NAME) 

re: fclean all

.PHONY: clean
