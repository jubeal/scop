NAME				=		scop

RED 				=		\033[1;31m
CYAN 				=		\033[1;36m
GREEN 			=		\033[1;32m
NO_COLOR 		=		\033[0m

# Directories

INC_DIR			= 	./includes
SRC_DIR			= 	./src
OBJ_DIR			=		./obj

# Src

SRC 				= 	main.cpp\
								window/glad.cpp\
								window/inputs.cpp\
								display/objects.cpp\
								display/shaders.cpp\
								display/texture.cpp\
								display/camera.cpp\
								math/matrix.cpp\
								math/vector.cpp\
								parsing/parsing.cpp\
								logs.cpp\

# Obj

OBJ 				= 	$(SRC:.cpp=.o)

# Files

INC_FILES 	= $(addprefix $(INC_DIR)/, $(INC))
SRC_FILES 	= $(addprefix $(SRC_DIR)/, $(SRC))
OBJ_FILES 	= $(addprefix $(OBJ_DIR)/, $(OBJ))

#Flags

CXX 				= g++
CXXFLAGS 		= -std=c++17 -Wall -Wextra -Werror -O2
LDFLAGS			=

# GLFW3

PKG_LIBS 		= glfw3
PKG_CFLAGS 	= $(shell pkg-config --cflags $(PKG_LIBS))
PKG_LDLIBS 	= $(shell pkg-config --libs $(PKG_LIBS))

#Rules

all: 						$(NAME)

$(NAME): 				$(OBJ_FILES)
								@echo "$(CYAN)Creation of binary ...$(NO_COLOR)"
								@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(PKG_LDLIBS)
								@echo "$(GREEN)Binary created ...$(NO_COLOR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
								@mkdir -p $(dir $@)
								@$(CXX) $(CXXFLAGS) $(PKG_CFLAGS) -c $< -o $@ -I $(INC_DIR)
								@echo "$(GREEN)$@ created ...$(NO_COLOR)\r" $(STR)

clean:
	@echo "Removal of .o files ..."
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Files .o deleted\n$(NO_COLOR)"

fclean: clean
	@echo "Removal of binaries and execution files..."
	@rm -f $(NAME)
	@echo "$(RED)Binaries and execution files deleted\n$(NO_COLOR)"

re: fclean all

test:
	@echo "$(OBJ_FILES)"

.PHONY: all, clean, fclean, re