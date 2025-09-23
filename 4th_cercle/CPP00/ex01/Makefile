
# ==== PROGRAM NAME ==== #

NAME 				= 	phonebook

# ==== COMPILER AND FLAGS ==== #

CC 					= 	c++
CFLAGS 				= 	-Wall -Wextra -Werror 	\
						-std=c++98

# ==== FILES SRC ==== #

SRC_ROOT   			=  	main.cpp				\
						phonebook.cpp			\
						contact.cpp				\
						utils.cpp

SRC        			= $(SRC_ROOT)

OBJ_DIR				= 	obj
OBJ					= 	$(SRC:%.cpp=$(OBJ_DIR)/%.o)

# ==== RULES ==== #

all 				: 	$(NAME)

$(NAME) 			: 	$(OBJ)
			  		  	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o		: 	%.cpp
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $< → $@"
			  		  	@$(CC) $(CFLAGS) -c $< -o $@

clean :
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re