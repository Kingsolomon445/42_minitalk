SERVER	=	server
CLIENT	=	client

SERVER_BONUS	= 	server_bonus
CLIENT_BONUS	=	client_bonus

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm -rf

S_SRC	=	server.c
C_SRC	=	client.c
BS_SRC	=	server_bonus.c
BC_SRC	=	client_bonus.c

S_OBJ	=	$(S_SRC:.c=.o)
C_OBJ	= 	$(C_SRC:.c=.o)
BS_OBJ	=	$(BS_SRC:.c=.o)
BC_OBJ	= 	$(BC_SRC:.c=.o)

LIBFT_PATH	=	./libft
LIBFT	=	$(LIBFT_PATH)/libft.a

all:	$(LIBFT) $(SERVER) $(CLIENT)

$(LIBFT):
	if [ ! -d "$(LIBFT_PATH)" ]; then \
		git clone https://github.com/Kingsolomon445/42_libft libft; \
	fi
	make -C $(LIBFT_PATH) all
	

bonus:	$(LIBFT) $(SERVER_BONUS) $(CLIENT_BONUS)


$(SERVER): $(S_OBJ)
	$(CC) $(CFLAGS) $(LIBFT) -o $@ $(S_OBJ)

$(CLIENT): $(C_OBJ)
	$(CC) $(CFLAGS) $(LIBFT) -o $@ $(C_OBJ)

$(SERVER_BONUS): $(BS_OBJ)
	$(CC) $(CFLAGS) $(LIBFT) -o $@ $(BS_OBJ)

$(CLIENT_BONUS): $(BC_OBJ)
	$(CC) $(CFLAGS) $(LIBFT) -o $@ $(BC_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(C_SRC) -c
	$(CC) $(CFLAGS) $(S_SRC) -c
	$(CC) $(CFLAGS) $(BC_SRC) -c
	$(CC) $(CFLAGS) $(BS_SRC) -c

clean:
	$(RM) $(S_OBJ) $(C_OBJ) $(BS_OBJ) $(BC_OBJ)
	if [ -d "$(LIBFT_PATH)" ]; then \
		make -C $(LIBFT_PATH) clean; \
	fi

fclean:	clean
	$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	if [ -d "$(LIBFT_PATH)" ]; then \
		make -C $(LIBFT_PATH) fclean; \
	fi

re:	fclean all bonus

.PHONY:	all clean fclean re bonus

