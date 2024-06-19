NAME = cub3d

FLAGS = -Wall -Werror -Wextra -fPIE

FILES = src/main.c\
		src/parser.c\
		src/free.c\
		src/map_check.c\
		src/game.c\
		src/keypress.c\
		src/raycasting.c\
		src/rendering.c\
		src/start_map.c\

OBJS = $(FILES:.c=.o)

LIBFT_PATH = ./libft 

MLX_PATH = ./MLX42

LIBFT = libft/libft.a

MLX = $(MLX_PATH)/libmlx42.a

LIB_SYS  = -ldl -DEBUG=1 -Iinclude -lm -lglfw -L"usr/lib/x86_64-linux-gnu/"

all : $(NAME) $(LIBFT) $(MLX)

$(LIBFT) :
	@make -s -C $(LIBFT_PATH)

$(MLX) :
	@make -s -C $(MLX_PATH)

$(NAME) : $(OBJS) $(LIBFT) $(MLX)
	@gcc $(FLAGS) $(FILES) $(LIBFT) $(MLX) $(LIB_SYS) -o $(NAME)

$(OBJS) : $(FILES)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@make clean -s -C $(LIBFT_PATH)
	@make clean -s -C $(MLX_PATH)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -s -C $(LIBFT_PATH)
	@make fclean -s -C $(MLX_PATH)

re : fclean all

.PHONY: all clean fclean re