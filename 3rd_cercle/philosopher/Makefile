
# ==== PROGRAM NAME ==== #

NAME 				= 	philosopher

# ==== COMPILER AND FLAGS ==== #

CC 					= 	cc 
CFLAGS 				= 	-Wall -Wextra -Werror 	\
						-I. 					\
						-I$(LIBFT_DIR) 

# ==== FILES SRC ==== #

SRC_ROOT   			=  	main.c		 	\
						program.c 		
									
SRC_UTIL   			= 	./utils/1_utils.c 

SRC        			= $(SRC_ROOT) $(SRC_UTIL)

UTILS_DIR 			= 	utils
OBJ_DIR				= 	obj
OBJ					= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== LIBFT / PRINTF ==== #

LIBFT_DIR			= 	./libft
LIBFT_A 			= 	$(LIBFT_DIR)/libft.a 

# ==== RULES ==== #

all 				: 	$(LIBFT_A) $(NAME)

$(NAME) 			: 	$(OBJ)
			  		  	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_A)

$(OBJ_DIR)/%.o		: 	%.c
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $< → $@"
			  		  	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A) 			:
					  	@make -s -C $(LIBFT_DIR)

clean :
					  	@make -s -C $(LIBFT_DIR) clean
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@make -s -C $(LIBFT_DIR) fclean
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re