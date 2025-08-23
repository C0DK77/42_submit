
# ==== PROGRAM NAME ==== #

NAME 			= 	libft.a

# ==== CREATE STATIC ARCHIVE ==== #

AR 				= 	ar rcs

# ==== FLAGS AND COMPILER ==== #

CC 				= 	cc
CFLAGS 			= 	-Wall -Wextra -Werror

# ==== FILES ==== #

SRC 			= 	ft_atoi.c ft_bzero.c ft_calloc.c ft_convert_bit_char.c	\
					ft_convert_char_to_bit.c ft_intlen.c ft_isalnum.c 		\
					ft_isalpha.c ft_isascii.c ft_isdigit.c 					\
					ft_isdoublequote.c ft_isoperator.c ft_isprint.c			\
					ft_issinglequote.c ft_isspace.c ft_itoa.c 				\
					ft_lstadd_back.c ft_lstadd_front.c 						\
					ft_lstclear.c ft_lstdelone.c ft_lstiter.c ft_lstlast.c	\
					ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_memchr.c 		\
					ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c		\
					ft_putchar_fd.c ft_putchar.c ft_putendl_fd.c 			\
					ft_putnbr_fd.c ft_putnbr.c ft_putstr_fd.c ft_putstr.c	\
					ft_split.c ft_strchr.c ft_strcmp.c ft_strcpy.c 			\
					ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c 	\
					ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c 		\
					ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c 		\
					ft_tolower.c ft_toupper.c ft_isquote.c 					\
					ft_has_unclosed_quote.c ft_strjoin_free.c ft_strndup.c	\
					ft_atoll.c ft_isnumeric.c ft_atoi64.c ft_strslen.c		\
					ft_strjoin_three.c ft_free_tab.c
					
OBJ_DIR 		= 	obj
OBJ 			= 	$(SRC:%.c=$(OBJ_DIR)/%.o)

# ==== RULES ==== #

all				: 	$(OBJ_DIR) $(NAME)

$(OBJ_DIR)		:
					@mkdir -p $(OBJ_DIR)

$(NAME)			: 	$(OBJ)
					@$(AR) $(NAME) $(OBJ)

$(OBJ_DIR)/%.o	: 	%.c
					@echo "Compilation de $<"
					@$(CC) $(CFLAGS) -c $< -o $@

clean			:
					@rm -rf $(OBJ_DIR)

fclean			: 	clean
					@rm -f $(NAME) 

re				: 	fclean all

.PHONY 			: 	all clean fclean re
