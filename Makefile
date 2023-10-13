CC := g++
CFLAGS := -std=c++17 -Wall -Wextra -Iincludes
LDFLAGS := 
TARGET := main
OBJ_DIR := obj
SRC_DIR := src

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ_DIR)/main.o $(OBJ_DIR)/diretorio.o
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	rm -rf *.o $(OBJ_DIR) $(TARGET)