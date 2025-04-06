MAKEFLAGS += --no-print-directory
# --- Basic configuration --- #
NAME        = ft_malcolm
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -Iinclude/ -Iinclude/libft/includes
LIBS        = # -lpcap (if additional libraries are needed)

# --- Directorios --- #
SRC_DIR     = src/
OBJ_DIR     = obj/

# --- Libft library --- #
LIBFT_DIR   = include/libft
LIBFT       = $(LIBFT_DIR)/libft.a

# --- Sources and objects --- #
SRC_FILES   = main.c \
            error_utils.c \
#			arp_handler.c \
            network_utils.c \
            signal_handler.c

SRC         = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ         = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# --- Colors (optional) --- #
GREEN       = \033[0;32m
RED         = \033[0;31m
BLUE        = \033[0;34m
NC          = \033[0m

# --- Rules --- #
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(GREEN)[✔] Enlazando objetos...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@ $(LIBS)
	@echo "$(GREEN)[✔] $(NAME) compilado correctamente!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
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