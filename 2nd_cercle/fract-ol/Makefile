
# ==== PROGRAM NAME ==== #

NAME 				= 	fractol

# ==== COMPILER AND FLAGS ==== #

CC 					= 	cc 
CFLAGS 				= 	-Wall -Wextra -Werror 	\
						-I. 					\
						-I$(MLX_DIR) 			\
						-I$(LIBFT_DIR) 

# ==== FILES SRC ==== #

SRC		   			=  	fractol.c 			\
						init.c 				\
						events.c			\
						draw.c 				

OBJ_DIR				= 	obj
OBJ					= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== LIBFT / PRINTF ==== #

LIBFT_DIR			= 	./libft
MLX_DIR    			= 	./mlx
LIBFT_A 			= 	$(LIBFT_DIR)/libft.a 
MLX_LIBS  			= 	-L$(MLX_DIR) -lmlx -lX11 -lXext -lbsd -lm

# ==== RULES ==== #

all 				: 	$(LIBFT_A) $(NAME)

$(NAME) 			: 	$(OBJ)
			  		  	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT_A) $(MLX_LIBS)

$(OBJ_DIR)/%.o		: 	%.c $(LIBFT_A)
					  	@mkdir -p $(dir $@)
			  		  	@echo "Compilation de $<"
			  		  	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A) 			:
					  	@make -s -C $(LIBFT_DIR)
					  	@make bonus -s -C $(LIBFT_DIR)

clean :
					  	@make -s -C $(LIBFT_DIR) clean
					  	@rm -rf $(OBJ_DIR)
	
fclean 				: 	clean 
					  	@make -s -C $(LIBFT_DIR) fclean
					  	@rm -f $(NAME)
	
re 					: 	fclean all
	
.PHONY 				: 	all clean fclean re