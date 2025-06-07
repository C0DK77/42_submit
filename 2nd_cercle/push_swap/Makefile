
# ==== PROGRAM NAME ==== #

NAME 				= 	push_swap

# ==== COMPILER AND FLAGS ==== #

CC 					= 	cc 
CFLAGS 				= 	-Wall -Wextra -Werror 	\
						-I. 					\
						-I$(PRINTF_DIR) 		\
						-I$(LIBFT_DIR) 

# ==== FILES SRC ==== #

SRC_ROOT   			=  	push_swap.c 	\
						sort.c 			\
						functions.c
SRC_UTIL   			= 	./utils/1_utils.c \
						./utils/2_utils.c \
						./utils/3_utils.c \
						./utils/4_utils.c \
						./utils/lists.c \
						./utils/verif.c
SRC        			= $(SRC_ROOT) $(SRC_UTIL)

UTILS_DIR 			= 	utils
OBJ_DIR				= 	obj
OBJ					= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== LIBFT / PRINTF ==== #

LIBFT_DIR			= 	./libft
PRINTF_DIR 			= 	./printf
LIBFT_A 			= 	$(LIBFT_DIR)/libft.a 
PRINTF_A 			= 	$(PRINTF_DIR)/ft_printf.a 

# ==== RULES ==== #

all 				: 	$(LIBFT_A) $(PRINTF_A) $(NAME)

$(NAME) 			: 	$(OBJ)
			  		  	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_A) $(PRINTF_A)

$(OBJ_DIR)/%.o		: 	%.c
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $< → $@"
			  		  	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/utils/%.o: 	$(UTILS_DIR)/%.c
					  	@mkdir -p $(dir $@)
					  	@echo "Compilation de $< → $@"
					  	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A) 			:
					  	@make -s -C $(LIBFT_DIR)
					  	@make bonus -s -C $(LIBFT_DIR)

$(PRINTF_A) 		:
					  	@make -s -C $(PRINTF_DIR)

clean :
					  	@make -s -C $(LIBFT_DIR) clean
					  	@make -s -C $(PRINTF_DIR) clean
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@make -s -C $(LIBFT_DIR) fclean
					  	@make -s -C $(PRINTF_DIR) fclean
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re