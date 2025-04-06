# --- Configuración básica --- #
NAME        = ft_malcolm
CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -g
INCLUDES    = -Iinclude/
LIBS        = # -lpcap (si necesitas librerías adicionales)
SRC_DIR     = src/
OBJ_DIR     = obj/

# --- Fuentes y objetos --- #
SRC_FILES   = main.c \
			error_utils.c \
#			arp_handler.c \
			network_utils.c \
			signal_handler.c

SRC         = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ         = $(addprefix $(OBJ_DIR), $(SRC_FILES:.c=.o))

# --- Colores (opcional) --- #
GREEN       = \033[0;32m
RED         = \033[0;31m
BLUE        = \033[0;34m
NC          = \033[0m

# --- Reglas principales --- #
all: $(NAME)

$(NAME): $(OBJ)
	@echo "$(GREEN)[✔] Enlazando objetos...$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIBS)
	@echo "$(GREEN)[✔] $(NAME) compilado correctamente!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	@echo "$(BLUE)[⚙] Compilando: $<$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $@

# --- Limpieza --- #
clean:
	@echo "$(RED)[✗] Eliminando objetos...$(NC)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(RED)[✗] Eliminando ejecutable...$(NC)"

re: fclean all

# --- PHONY (evita conflictos con archivos) --- #
.PHONY: all clean fclean re