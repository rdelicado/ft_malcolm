CC = gcc
NAME = libft.a
CFLAGS = -Wall -Werror -Wextra -Iinclude
LIB = ar rcs

# Colors
GREEN = \033[0;32m
BLUE = \033[0;34m
YELLOW = \033[1;33m
RED = \033[0;31m
RESET = \033[0m
BOLD = \033[1m

# Directories
SRCDIR = src
OBJDIR = obj
INCDIR = include

# Automatically find all .c files in src and subdirectories
SRCS = $(shell find $(SRCDIR) -name "*.c" | sort)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TOTAL_FILES = $(words $(SRCS))
CURRENT = 0

# Create list of all object directories needed
OBJ_DIRS = $(sort $(dir $(OBJS)))

all: 
	@clear
	@$(MAKE) $(NAME) --no-print-directory

# Create all necessary object directories
$(OBJ_DIRS):
	@mkdir -p $@

# Universal compilation rule for any .c file in src/
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJ_DIRS)
	@$(call compile_file,$<,$@)

# Function to compile with progress bar
define compile_file
	$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	$(eval PERCENT := $(shell echo $$(($(CURRENT) * 100 / $(TOTAL_FILES)))))
	$(eval FILLED := $(shell echo $$(($(CURRENT) * 20 / $(TOTAL_FILES)))))
	$(eval BAR := $(shell printf "%*s" $(FILLED) "" | tr ' ' '='))
	$(eval SPACES := $(shell printf "%*s" $$((20 - $(FILLED))) ""))
	$(eval ARROW := $(shell if [ $(FILLED) -lt 20 ]; then printf ">"; fi))
	@if [ $(CURRENT) -eq 1 ]; then printf "\033[?25l"; fi
	@$(CC) $(CFLAGS) -c $1 -o $2 2>/dev/null
	@printf "\r$(BLUE)Compiling$(RESET) [$(GREEN)$(BAR)$(ARROW)$(SPACES)$(RESET)] $(YELLOW)%3d%%$(RESET) %-20s" $(PERCENT) "$(notdir $1)"
	@if [ $(CURRENT) -eq $(TOTAL_FILES) ]; then printf "\033[?25h\n"; fi
endef

$(NAME): $(OBJS)
	@printf "\n$(YELLOW)Creating library:$(RESET) $(BOLD)$(NAME)$(RESET)\n"
	@$(LIB) $(NAME) $(OBJS)
	@printf "$(GREEN)✅ Build completed successfully!$(RESET)\n"

clean:
	@printf "$(RED)🧹 Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJDIR)
	@printf "$(GREEN)✅ Clean completed!$(RESET)\n"

fclean: 
	@clear
	@$(MAKE) clean --no-print-directory
	@printf "$(RED)🗑️  Removing library...$(RESET)\n"
	@rm -f $(NAME)
	@printf "$(GREEN)✅ Full clean completed!$(RESET)\n"

re: fclean all

# Debug rule to show what files were found
debug:
	@echo "Found $(words $(SRCS)) source files:"
	@echo "$(SRCS)" | tr ' ' '\n' | nl
	@echo "\nObject files will be:"
	@echo "$(OBJS)" | tr ' ' '\n' | nl

.PHONY: all re fclean clean debug
