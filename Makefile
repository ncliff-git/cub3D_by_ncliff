NAME	= cub3D.a

HEADER	= includes/

SRC		=	main.c		\
			key_check.c	\
			movement.c	\
			render3d.c

CC		= gcc

SRC_DIR = $(addprefix src/, $(SRC))

OBJ		= $(patsubst src/%.c, obj/%.o, $(SRC_DIR))

OUT_DIR = obj

MKDIR_P	= mkdir -p

all: $(OUT_DIR) $(NAME)

obj/%.o:	src/%.c
	@$(CC) -Wall -Wextra -Werror -Imlxl -c $< -o $@

$(NAME):	$(OBJ)
	@$(CC) $(OBJ) mlx/libmlx.a -framework OpenGL -framework AppKit -o $(NAME)
	@echo '$(cgreen)Good compile!'

$(OUT_DIR):
	@$(MKDIR_P) $@
	@echo '$(cgreen)$@ dir create$(cwhite)'
	@echo "\033[1A"

re: fclean all

clean:
	@/bin/rm -rf $(OUT_DIR)
	@echo '$(ccred)$(OUT_DIR) delete$(cwhite)'

fclean: clean
	@/bin/rm -f $(NAME)
	@echo '$(ccred)$(NAME) file delete$(cwhite)'

cgreen=$(shell echo "\033[0;32m")
ccred=$(shell echo "\033[0;31m")
cwhite=$(shell echo "\033[0;0m")
