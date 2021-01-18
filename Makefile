NAME	= cub3D.a

SRC		= main.c

CC		= gcc

SRC_DIR = $(addprefix src/, $(SRC))

OBJ		= $(patsubst src/%.c, obj/%.o, src)

OUT_DIR = obj


MKDIR_P	= mkdir -p

all: $(OUT_DIR) $(NAME)

%.o:	%.c
	@$(CC) -Wall -Wextra -Werror -Imlxl -c $< -o $@

$(NAME):	$(OBJ)
	$(CC) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@echo '$(cgreen)Good compile!'

$(OUT_DIR):
	@$(MKDIR_P) $@
	@echo '$(cgreen)$@ dir create$(cwhite)'

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
