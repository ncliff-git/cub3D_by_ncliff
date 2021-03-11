NAME	= cub3D

HEADER	= includes/cub3d.h

SRC		=	main.c		\
			key_check.c	\
			movement.c	\
			get_next_line.c\
			get_next_line_utils.c\
			parser_file.c \
			parser_file_r.c\
			parser_map.c\
			valid_map.c\
			parser_texture.c\
			parser_color.c\
			spr_list.c\
			sprite.c\
			render_wall_1.c\
			render_wall_2.c\
			render_spr.c\
			screen.c\
			parser_file_dop.c\
			mlx_and_msg.c\
			check_and_init.c\
			texture_init.c\
			sprite2.c

CC		= gcc

INCLUDE = -Imlx -Iincludes

SRC_DIR = $(addprefix src/, $(SRC))

OBJ		= $(patsubst src/%.c, obj/%.o, $(SRC_DIR))

OUT_DIR = obj

MKDIR_P	= mkdir -p

LIBFT	= libft/libft.a

all: $(OUT_DIR) $(LIBFT) $(MLX_CR) $(NAME)

obj/%.o:	src/%.c
	@$(CC) -g -Wall -Wextra -Werror -Imlx -c $< -o $@

$(NAME):	$(OBJ) $(LIBFT) $(FT_PRINTF) $(HEADER)
	@$(CC) $(OBJ) mlx/libmlx.a $(INCLUDE) $(LIBFT) -framework OpenGL -framework AppKit -o $(NAME)
	@echo '$(cgreen)Good compile!'

$(LIBFT):
	@cd libft && make
	@echo '$(cgreen)Libft compile$(cwhite)'

$(OUT_DIR):
	@$(MKDIR_P) $@
	@echo '$(cgreen)$@ dir create$(cwhite)'
	@echo "\033[1A"

$(MLX_CR):
	@cd mlx && make re

re: fclean all

clean:
	@/bin/rm -rf $(OUT_DIR)
	@cd libft && make clean
	@echo '$(ccred)$(OUT_DIR) delete$(cwhite)'

fclean: clean
	@cd libft && make fclean
	@/bin/rm -f $(NAME)
	@echo '$(ccred)$(NAME) file delete$(cwhite)'

.PHONY: clean fclean

cgreen=$(shell echo "\033[0;32m")
ccred=$(shell echo "\033[0;31m")
cwhite=$(shell echo "\033[0;0m")
