NAME = wolf3d

CC = gcc

CFLAGS = -I./SDL2_mac/include -I./include

SRCS = main.c \
		graphiclib.c \
		parse.c

SRCF = ./srcs/

OBJS = $(addprefix $(SRCF), $(SRCS:.c=.o))

LIB = ./SDL2_mac/lib

clean:
	rm -rf $(OBJS)


fclean: clean


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) -o ./bin/$(NAME) $(OBJS) -L$(LIB) -lSDL2 -lm
