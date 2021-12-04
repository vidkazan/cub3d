NAME = cub3D

CC = gcc

FLAGS = -I./mlx

LIBS = -L./mlx -lmlx libft/libft.a -framework OpenGL -framework AppKit

SRC = 1main.c 2dda.c 2render.c 3init.c 4move.c 5texture.c 6map_check.c 7rec_texture.c lib_utils.c Get_Next_Line/get_next_line.c Get_Next_Line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
	@ echo OK!

mlx:
	@ make -C mlx

$(NAME): $(OBJ) mlx
	@ $(CC) -o $(NAME) $(FLAGS) $(LIBS) $(OBJ)

%.o:%.c cub3d.h
	@ $(CC) $(FLAGS) -c -o $@ $<

clean:
	make clean -C mlx
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx
