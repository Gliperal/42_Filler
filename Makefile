CC=gcc
CFLAGS=-Wall -Wextra -Werror
CSRC=filler.c \
	game.c \
	heatmap.c \
	input_map.c \
	input_piece.c \
	input_player.c \
	map.c \
	map_display.c \
	map_calculate.c \
	piece.c
OBJS=filler.o \
	game.o \
	heatmap.o \
	input_map.o \
	input_piece.o \
	input_player.o \
	map.o \
	map_display.o \
	map_calculate.o \
	piece.o
GCH=*.gch
RM=rm -rf
LOGIN=nwhitlow
NAME=$(LOGIN).filler

$(NAME):
	$(CC) $(CFLAGS) -c $(CSRC) -I libft
	$(CC) $(OBJS) -o $(NAME) -Llibft -lft

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

ft:
	make -C libft re
	make -C libft clean
