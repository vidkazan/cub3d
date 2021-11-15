NAME = cub3d

CC = gcc

FLAGS = -I./mlx

LIBS = -L./mlx -lmlx libft/libft.a -framework OpenGL -framework AppKit

SRC = main.c

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
