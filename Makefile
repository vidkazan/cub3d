NAME = cub3D

SRC = main.c dda.c render.c init.c move.c texture.c get_tex.c draw_tex.c map_check.c set_player_pos.c file_check.c copy_file_content.c rec_texture.c rec_bg_color.c lib_utils.c lib_utils2.c lib_utils3.c Get_Next_Line/get_next_line.c Get_Next_Line/get_next_line_utils.c

LIBS = libft/libft.a 

HEADER = cub3d.h

CC = gcc

CFLAGS		=	-Wall -Wextra -Werror

MLX_FLAGS = -I./mlx -L./mlx -lmlx -framework OpenGL -framework AppKit

RM			=	rm -f

OFF_COLOR		=	\033[0m
RED				=	\033[0;31m
GREEN			=	\033[0;32m
YELLOW			=	\033[0;33m
L_BLUE			=	\033[0;34m
PURPLE			=	\033[0;35m
L_BLUE			=	\033[0;36m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	@ say Coooob!
	@$(CC) $(MLX_FLAGS) $(LIBS) $(SRC) -o $(NAME)
	@echo "$(GREEN)Cub3D compiled!$(OFF_COLOR)"
	@echo "${GREEN}For $(YELLOW)START${GREEN} press command: $(YELLOW) ./cub3D maps/1.CUB ${GREEN}! ${OFF_COLOR}"
	@ say 3D uspieshno!

clean:
	@make clean -C mlx
	@echo "$(RED)Object files deleted!$(OFF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "${RED}🗑 Program deleted!${OFF_COLOR}"

re: fclean all
