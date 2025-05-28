GREEN  		= \033[0;32m
YELLOW 		= \033[0;33m
RED    		= \033[0;31m
RESET  		= \033[0m
CLEAR		= \033[K\r
NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
FLAGS		= -pthread #-fsanitize=thread -g3
AR			= ar rcs
INCLUDES	= -I./headers/
# LIBFT_DIR	= libft
# LIBFT		= $(addprefix $(LIBFT_DIR)/, libft.a)
SRC			= src/main.c \
			  src/ohter_funcions.c \
			  src/philosophers_action.c \
			  src/start_dining.c \
			  src/parse_and_init.c \
			  src/utils/ph_atoi.c \
			  src/utils/ph_atol.c
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
