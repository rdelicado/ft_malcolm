MAKEFLAGS += --no-print-directory
# --- Basic configuration --- #
NAME        = ft_malcolm
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -Iinclude/ -Ilibft/includes
LIBS        = # -lpcap (if additional libraries are needed)

# --- Directorios --- #
SRC_DIR     = src/
OBJ_DIR     = obj/

# --- Libft library --- #
LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

# --- Sources and objects --- #
SRC_FILES   = $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES	= $(patsubst $(SRC_DIR)%.c,$(OBJ_DIR)%.o,$(SRC_FILES))

# --- Colors (optional) --- #
GREEN       = \033[0;32m
RED         = \033[0;31m
BLUE        = \033[0;34m
NC          = \033[0m

# --- Rules --- #
all: $(NAME)

$(NAME): $(OBJ_FILES) $(LIBFT)
	@echo "$(GREEN)[✔] Enlazando objetos...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $@ $(LIBS)
	@echo "$(GREEN)[✔] $(NAME) compilado correctamente!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@echo "$(BLUE)[⚙] Compilando: $<$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

$(LIBFT):
	@echo "$(BLUE)[⚙] Compilando libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR)

# --- Cleaning --- #
clean:
	@echo "$(RED)[✗] Eliminando objetos...$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)[✗] Eliminando ejecutable...$(NC)"
	@rm -f $(NAME)
	@echo "$(RED)[✗] Limpiando libft...$(NC)"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

# --- PHONY (prevents conflicts with files) --- #
.PHONY: all clean fclean re