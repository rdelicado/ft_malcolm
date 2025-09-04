NAME        = libft.a
CC          = gcc
CFLAGS      = -Wall -Werror -Wextra -Iincludes -g
LIB         = ar rcs

SRCS = \
    src/ft_bzero.c src/ft_isalnum.c src/ft_isalpha.c src/ft_isascii.c src/ft_isprint.c\
    src/ft_isdigit.c src/ft_memchr.c src/ft_memcpy.c src/ft_memset.c\
    src/ft_strchr.c src/ft_strlcat.c src/ft_strlcpy.c src/ft_strlen.c src/ft_strncmp.c\
    src/ft_strrchr.c src/ft_tolower.c src/ft_toupper.c src/ft_memcmp.c src/ft_strnstr.c\
    src/ft_atoi.c src/ft_calloc.c src/ft_strdup.c src/ft_substr.c src/ft_memmove.c\
    src/ft_strjoin.c src/ft_strtrim.c src/ft_strmapi.c src/ft_striteri.c src/ft_putchar_fd.c\
    src/ft_putstr_fd.c src/ft_putendl_fd.c src/ft_putnbr_fd.c src/ft_itoa.c src/ft_split.c\
	src/ft_strarrlen.c src/ft_strarrfree.c src/ft_is_hex.c

OBJS = $(SRCS:src/%.c=obj/%.o)

BONUS_SRCS = \
    src/ft_lstnew_bonus.c src/ft_lstadd_front_bonus.c src/ft_lstsize_bonus.c\
    src/ft_lstlast_bonus.c src/ft_lstadd_back_bonus.c src/ft_lstdelone_bonus.c\
    src/ft_lstclear_bonus.c src/ft_lstiter_bonus.c src/ft_lstmap_bonus.c

BONUS_OBJS = $(BONUS_SRCS:src/%.c=obj/%.o)

# Colores e iconos
GREEN  = \033[0;32m
RED    = \033[0;31m
BLUE   = \033[0;34m
NC     = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)[✔] Enlazando objetos...$(NC)"
	@$(LIB) $(NAME) $(OBJS)
	@echo "$(GREEN)[✔] $(NAME) creado correctamente!$(NC)"

bonus: $(OBJS) $(BONUS_OBJS)
	@echo "$(GREEN)[✔] Enlazando objetos (bonus)...$(NC)"
	@$(LIB) $(NAME) $(OBJS) $(BONUS_OBJS)
	@echo "$(GREEN)[✔] $(NAME) (bonus) creado correctamente!$(NC)"

obj/%.o: src/%.c | obj
	@echo "$(BLUE)[⚙] Compilando: $<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

obj:
	@mkdir -p obj
	@echo "$(BLUE)[⚙] Carpeta 'obj' creada$(NC)"

clean:
	@echo "$(RED)[✗] Eliminando archivos objeto...$(NC)"
	@rm -f $(OBJS) $(BONUS_OBJS)
	@rm -rf obj

fclean: clean
	@echo "$(RED)[✗] Eliminando biblioteca $(NAME)...$(NC)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus re fclean clean