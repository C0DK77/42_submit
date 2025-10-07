
# ==== PROGRAM NAME ==== #

NAME 				= 	philo

# ==== COMPILER AND FLAGS ==== #

CC 					= 	cc 
CFLAGS 				= 	-I. 					\
						-g -Wall -Wextra -Werror					

# ==== FILES SRC ==== #

SRC_ROOT   			=  	main.c	
									
SRC_UTIL   			=	./program/init.c 		\
						./program/routine.c		\
 						./program/utils_1.c 	\
						./program/utils_2.c 	\
						./program/program.c 	\
						./program/monitor.c

SRC        			= $(SRC_ROOT) $(SRC_UTIL)

OBJ_DIR				= 	obj
OBJ					= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

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