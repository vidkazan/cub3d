NAME = cub3D

CC = gcc

FLAGS = -I./mlx -Wall -Wextra -Werror

LIBS = -L./mlx -lmlx libft/libft.a -framework OpenGL -framework AppKit

SRC = main.c dda.c render.c init.c move.c texture.c get_tex.c draw_tex.c map_check.c set_player_pos.c file_check.c copy_file_content.c rec_texture.c rec_bg_color.c lib_utils.c lib_utils2.c lib_utils3.c Get_Next_Line/get_next_line.c Get_Next_Line/get_next_line_utils.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
	@ echo OK!

mlx:
	@ make -C mlx

$(NAME): $(OBJ) mlx
	@ $(CC) -o $(NAME) $(FLAGS) $(LIBS) $(OBJ)
	@ rm -f $(OBJ)

%.o:%.c cub3d.h
	@ $(CC) $(FLAGS) -c -o $@ $<

clean:
	make clean -C mlx
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx
