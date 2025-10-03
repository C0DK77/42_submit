
# ==== PROGRAM NAME ==== #

NAME 				= 	philosopher

# ==== COMPILER AND FLAGS ==== #

CC 					= 	cc 
CFLAGS 				= 	-Wall -Wextra -Werror 	\
						-I. 					

# ==== FILES SRC ==== #

SRC_ROOT   			=  	main.c	
									
SRC_UTIL   			= 	./program/utils.c 		\
						./program/init.c 		\
						./program/routine.c		\
						./program/monitor.c

SRC        			= $(SRC_ROOT) $(SRC_UTIL)

UTILS_DIR 			= 	utils
OBJ_DIR				= 	obj
OBJ					= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== LIBFT / PRINTF ==== #

LIBFT_DIR			= 	./libft
LIBFT_A 			= 	$(LIBFT_DIR)/libft.a 

# ==== RULES ==== #

all 				: 	$(NAME)

$(NAME) 			: 	$(OBJ)
			  		  	@$(CC) $(CFLAGS) -o $@ $^ 

$(OBJ_DIR)/%.o		: 	%.c
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $< → $@"
			  		  	@$(CC) $(CFLAGS) -c $< -o $@

clean :
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re