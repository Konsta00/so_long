# ========================================
#           Project Information
# ========================================

NAME        := so_long

# Compiler and Flags
CC          := cc
CFLAGS      := -Wall -Wextra -Werror

# Directories
SRC_DIR     := src
GAME_DIR    := $(SRC_DIR)/game
MAP_DIR     := $(SRC_DIR)/map
UTILS_DIR   := $(SRC_DIR)/utils
OBJ_DIR     := obj
LIBFT_DIR   := libft
MLX_DIR     := minilibx

# Source Files
SRCS        :=  $(GAME_DIR)/game_engine.c \
				$(GAME_DIR)/game_enemy.c \
                $(GAME_DIR)/game_controls.c \
                $(GAME_DIR)/game_images.c \
                $(GAME_DIR)/game_render.c \
                $(MAP_DIR)/map_loader.c \
                $(MAP_DIR)/map_parser.c \
                $(MAP_DIR)/map_positions.c \
                $(MAP_DIR)/map_utils.c \
                $(MAP_DIR)/map_validate.c \
                $(UTILS_DIR)/utils.c \
				$(SRC_DIR)/so_long.c


# Object Files (same structure as source, in obj/)
OBJS        := $(SRCS:.c=.o)
OBJS_DIRS   := $(sort $(dir $(OBJS)))

# Libraries
LIBFT       := $(LIBFT_DIR)/libft.a
MLX_LIB     := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lbsd

# Includes
INC         := -Iinclude -I$(LIBFT_DIR)/include -I$(MLX_DIR)

# ========================================
#               Colors
# ========================================

GREEN       := \033[0;32m
YELLOW      := \033[0;33m
RESET       := \033[0m

# ========================================
#               Rules
# ========================================

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)[Linking]$(RESET) $(NAME)"
	@$(CC) $(CFLAGS) $(INC) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)
	@echo "$(GREEN)✔ $(NAME) built successfully!$(RESET)"

# Compile rule (create obj/ tree if needed)
%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(GREEN)[Compiling]$(RESET) $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)[Building]$(RESET) libft"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@echo "$(YELLOW)[Cleaning]$(RESET) object files"
	@rm -rf $(SRC_DIR)/*.o $(GAME_DIR)/*.o $(MAP_DIR)/*.o $(UTILS_DIR)/*.o
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(YELLOW)[Removing]$(RESET) $(NAME)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(GREEN)✔ All files removed successfully!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
