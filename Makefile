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

FT_PRINTF_PATH	=	./ft_printf
FT_PRINTF		=	$(FT_PRINTF_PATH)/libftprintf.a

$(FT_PRINTF):
	make -C $(FT_PRINTF_PATH) all
	
all:	$(FT_PRINTF) $(SERVER) $(CLIENT)

bonus:	$(FT_PRINTF) $(SERVER_BONUS) $(CLIENT_BONUS)


$(SERVER): $(S_OBJ)
	$(CC) $(CFLAGS) $(FT_PRINTF) -o $@ $(S_OBJ)

$(CLIENT): $(C_OBJ)
	$(CC) $(CFLAGS) $(FT_PRINTF) -o $@ $(C_OBJ)

$(SERVER_BONUS): $(BS_OBJ)
	$(CC) $(CFLAGS) $(FT_PRINTF) -o $@ $(BS_OBJ)

$(CLIENT_BONUS): $(BC_OBJ)
	$(CC) $(CFLAGS) $(FT_PRINTF) -o $@ $(BC_OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(C_SRC) -c
	$(CC) $(CFLAGS) $(S_SRC) -c
	$(CC) $(CFLAGS) $(BC_SRC) -c
	$(CC) $(CFLAGS) $(BS_SRC) -c

clean:
	make -C $(FT_PRINTF_PATH) clean
	$(RM) $(S_OBJ) $(C_OBJ) $(BS_OBJ) $(BC_OBJ)

fclean:	clean
	make -C $(FT_PRINTF_PATH) fclean
	$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)

re:	fclean all bonus

.PHONY:	all clean fclean re bonus

