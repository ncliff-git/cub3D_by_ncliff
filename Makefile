NAME	= cub3D

HEADER	= includes/

SRC		=	main.c		\
			key_check.c	\
			movement.c	\
			render_2d.c	\
			get_next_line.c\
			get_next_line_utils.c\
			parser_file.c \
			parser_file_r.c\
			parser_map.c\
			valid_map.c\
			parser_texture.c\
			parser_color.c\
			spr_list.c\
			sprite.c

CC		= gcc

SRC_DIR = $(addprefix src/, $(SRC))

OBJ		= $(patsubst src/%.c, obj/%.o, $(SRC_DIR))

OUT_DIR = obj

MKDIR_P	= mkdir -p

LIBFT	= libft/libft.a

FT_PRINTF = ft_printf/libftprintf.a

all: $(OUT_DIR) $(LIBFT) $(FT_PRINTF) $(NAME)

obj/%.o:	src/%.c
	@$(CC) -g -Wall -Wextra -Werror -Imlxl -c $< -o $@

$(NAME):	$(OBJ) $(LIBFT) $(FT_PRINTF)
	@$(CC) $(OBJ) mlx/libmlx.a $(LIBFT) $(FT_PRINTF) -framework OpenGL -framework AppKit -o $(NAME)
	@echo '$(cgreen)Good compile!'

$(LIBFT):
	@cd libft && make
	@echo '$(cgreen)Libft compile$(cwhite)'

$(FT_PRINTF):
	@cd ft_printf && make
	@echo '$(cgreen)ft_printf compile$(cwhite)'

$(OUT_DIR):
	@$(MKDIR_P) $@
	@echo '$(cgreen)$@ dir create$(cwhite)'
	@echo "\033[1A"

re: fclean all

clean:
	@/bin/rm -rf $(OUT_DIR)
	@cd libft && make fclean
	@echo '$(ccred)$(OUT_DIR) delete$(cwhite)'

fclean: clean
	@/bin/rm -f $(NAME)
	@echo '$(ccred)$(NAME) file delete$(cwhite)'

cgreen=$(shell echo "\033[0;32m")
ccred=$(shell echo "\033[0;31m")
cwhite=$(shell echo "\033[0;0m")
