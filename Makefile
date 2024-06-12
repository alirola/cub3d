NAME = cub3d

FLAGS = -Wall -Werror -Wextra

FILES = main.c\
		parser.c\
		free.c\

OBJS = $(FILES:.c=.o)

LIBFT_PATH = ./libft 

MLX_PATH = ./MLX42

LIBFT = libft/libft.a

MLX = $(MLX_PATH)/libmlx42.a

LIB_SYS = -lm -Iinclude -lglfw -L "/Users/alirola-/.brew/opt/glfw/lib/"

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