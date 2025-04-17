NAME		= cub3D

BONUS_NAME = cub3D_bonus

COREKIT_PATH = ./lib/corekit
MLX_PATH = ./lib/mlx

VALGRIND =  valgrind --leak-check=full --track-origins=yes --track-fds=yes --show-leak-kinds=all --suppressions=mlx.supp

INCLUDES = -I$(COREKIT_PATH)/includes -I$(MLX_PATH) -I./includes

SRC = src/main.c \
	src/init_game.c \
	src/parsing/parsing.c \
	src/parsing/parsing_utils.c \
	src/parsing/parsing_errors.c \
	src/parsing/asset_loading.c \
	src/parsing/map_loading/map_loading.c \
	src/parsing/map_loading/map_normalization.c \
	src/parsing/map_loading/map_validation.c \
	src/cleanup.c \
	src/window/display.c \
	src/window/hook.c \
	src/window/drawing.c \
	src/raycasting/dda.c \
	src/raycasting/raycasting.c \
	src/raycasting/draw_column.c \
	src/player/player.c \
	src/player/player_movement.c \

SRC_BONUS = src/window/minimap_bonus.c \
	src/window/gui_bonus.c \
	src/window/mouse_handling_bonus.c \
	src/window/door_handling_bonus.c \

FLAGS	= -g -O3
FLAGS	+= -Wall -Werror -Wextra
# FLAGS	+= -DSTRICT_MODE=0

$(NAME): $(SRC)
	@${MAKE} -sC $(COREKIT_PATH)
	@echo "$(GREEN)[COREKIT]:\t COREKIT CREATED$(RESET)"
	@${MAKE} -sC $(MLX_PATH) 2>/dev/null 1>/dev/null
	@cc $(SRC) $(INCLUDES) $(FLAGS) -lm -L$(COREKIT_PATH) -lcorekit -L$(MLX_PATH) -lmlx -lXext -lX11 -o $(NAME)
	@echo "$(GREEN)[$(NAME)]:\t PROJECT COMPILED$(RESET)"

all:$(NAME)

bonus: $(BONUS_NAME)

$(BONUS_NAME): $(SRC) $(SRC_BONUS)
	@${MAKE} -sC $(COREKIT_PATH)
	@echo "$(GREEN)[COREKIT]:\t COREKIT CREATED$(RESET)"
	@${MAKE} -sC $(MLX_PATH) 2>/dev/null 1>/dev/null
	@cc $(SRC) $(SRC_BONUS) $(INCLUDES) $(FLAGS) -lm -L$(COREKIT_PATH) -lcorekit -L$(MLX_PATH) -lmlx -lXext -lX11 -DBONUS=1 -o $(BONUS_NAME)
	@echo "$(GREEN)[$(BONUS_NAME)]:\t PROJECT COMPILED$(RESET)"

clean:
	@if [ -d "$(MLX_PATH)" ]; then \
		${MAKE} -sC $(MLX_PATH) clean >/dev/null 2>&1; \
		echo "$(RED)[MLX]:\t\t MLX CLEAN$(RESET)"; \
	fi
	@if [ -d "$(COREKIT_PATH)" ]; then \
		${MAKE} -C $(COREKIT_PATH) clean -s; \
		echo "$(RED)[COREKIT]:\t COREKIT CLEAN$(RESET)"; \
	fi

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)
	@if [ -d "$(COREKIT_PATH)" ]; then \
		${MAKE} -C $(COREKIT_PATH) fclean -s; \
		echo "$(RED)[COREKIT]:\t COREKIT FCLEAN$(RESET)"; \
	fi

re: download fclean corekit_pull all

rebonus: fclean bonus

#used to ensure that corekit is always up to date
corekit_pull:
	@git -C lib/corekit/ pull --quiet
	@echo "$(GREEN)[COREKIT]:\t PULLED$(RESET)";

MLX_LINK=https://github.com/42Paris/minilibx-linux/archive/refs/heads/master.zip
download:
	@if [ -d "lib" ]; then \
		echo "$(RED)[LIB]:\t\t LIB FOLDER ALREADY EXISTS$(RESET)"; \
	else \
		mkdir -p lib; \
	fi; \
	if [ ! -d "$(MLX_PATH)" ]; then \
		wget -q $(MLX_LINK) -O minilibx-linux.zip || (echo "$(RED)WRONG MLX LINK$(RESET)"; exit 1); \
		unzip -q minilibx-linux.zip; \
		mv minilibx-linux-master $(MLX_PATH); \
		rm -f minilibx-linux.zip*; \
		echo "$(GREEN)[MLX]:\t\t MLX DOWNLOADED$(RESET)"; \
	else \
		echo "$(RED)[MLX]:\t\t MLX ALREADY EXISTS$(RESET)"; \
	fi; \
	if [ ! -d "$(COREKIT_PATH)" ]; then \
		git clone -q https://github.com/Sheratan095/Corekit.git lib/corekit && \
		echo "$(GREEN)[COREKIT]:\t COREKIT DOWNLOADED$(RESET)"; \
	else \
		echo "$(RED)[COREKIT]:\t COREKIT ALREADY EXISTS$(RESET)"; \
	fi

remove_libs:
	@rm -fr $(MLX_PATH)
	@echo "$(RED)[MLX]:\t\t MLX REMOVED$(RESET)";
	@rm -fr $(COREKIT_PATH)
	@echo "$(RED)[COREKIT]:\t COREKIT REMOVED$(RESET)";
	@rm -fr lib/

args = maps/map_ok.cub

test: all
	 ./$(NAME) maps/map.cub

testbonus: $(BONUS_NAME)
	 ./$(BONUS_NAME) maps/map_bonus.cub

val: all
	$(VALGRIND) ./$(NAME) maps/map.cub

valbonus: $(BONUS_NAME)
	$(VALGRIND) ./$(BONUS_NAME) maps/map_bonus.cub

.PHONY: download

#COLORS

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
RESET=\033[0m
