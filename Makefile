NAME = wolf3d

CC = gcc

CFLAGS = -I./SDL2-2.0.7/include -I./include -Wall -Wextra -g

SRCS = main.c \
		graphiclib.c \
		parse.c \
		draw_map.c \
		game_mechanics.c \
		get_t_x_y.c \
		handle_keyboard.c \
		main_render.c \
		math.c \
		utils.c \
		procedural_colors.c \
		print_texture.c

SRCF = ./srcs/

all: $(NAME)

OBJS = $(addprefix $(SRCF), $(SRCS:.c=.o))

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

$(NAME): $(OBJS)
	@cd libft && make
	$(CC) -o $(NAME) $(OBJS) -lm -L./libft -lft `./SDL2-2.0.7/build/sdl2-config --cflags --libs`

re: fclean all

SDL2:
	cd SDL2-2.0.7 && mkdir build && cd build && ../configure --prefix ~/Library && make && make install
