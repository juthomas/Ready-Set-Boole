## Name of Project

NAME = multiplier

## Color for compilating (pink)

COLOR = \0033[1;35m

## List of Directories

OBJ_DIR = obj
SRC_DIR = .

CC = g++ $(FLAGS)

SRC_FT = multiplier

## List of Utilities

SRC = $(SRC_FT:%=$(SRC_DIR)/%.cpp)

OBJ = $(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

OBJ_DIRS = $(OBJ_DIR)

## Rules of Makefile

all: $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;30m[All OK]\0033[1;37m"

$(OBJ_DIRS):
	@mkdir -p $@
	@echo "$(COLOR)$@ \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDES)
	@$(CC) -c $< -o $@
	@echo "$(COLOR)$@ \033[100D\033[40C\0033[1;32m[Compiled]\0033[1;37m"

$(NAME): $(OBJ_DIRS) $(SRC)
	@$(MAKE) -s -j $(OBJ)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"
	@$(CC) $(OBJ) -o $@
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;32m[Created]\0033[1;37m"
	
clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(COLOR)Objects \033[100D\033[40C\0033[1;31m[Removed]\0033[1;37m"

fclean: clean
	@rm -f $(NAME)
	@echo "$(COLOR)$(NAME) \033[100D\033[40C\0033[1;31m[Removed]\0033[1;37m"

re: fclean all

define print_aligned_coffee
	@t=$(NAME); \
	l=$${#t};\
	i=$$((8 - l / 2));\
	echo "\0033[1;32m\033[3C\033[$${i}CAnd Your Program \"$(NAME)\" \0033[1;37m"
endef

coffee: all clean
	@echo ""
	@echo "                    {"
	@echo "                 {   }"
	@echo "                  }\0033[1;34m_\0033[1;37m{ \0033[1;34m__\0033[1;37m{"
	@echo "               \0033[1;34m.-\0033[1;37m{   }   }\0033[1;34m-."
	@echo "              \0033[1;34m(   \0033[1;37m}     {   \0033[1;34m)"
	@echo "              \0033[1;34m| -.._____..- |"
	@echo "              |             ;--."
	@echo "              |            (__  \ "
	@echo "              |             | )  )"
	@echo "              |   \0033[1;96mCOFFEE \0033[1;34m   |/  / "
	@echo "              |             /  / "
	@echo "              |            (  / "
	@echo "              \             | "
	@echo "                -.._____..- "
	@echo ""
	@echo ""
	@echo "\0033[1;32m\033[3C          Take Your Coffee"
	$(call print_aligned_coffee)

.PHONY: all clean fclean re coffee