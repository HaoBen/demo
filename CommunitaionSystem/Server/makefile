INC_DIR = ./include
BIN_DIR = ./bin
SRC_DIR = ./src
OBJ_DIR = ./obj
LIBS = -pthread

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(notdir $(SRC)))

TARGET = Server
BIN_TARGET = $(BIN_DIR)/$(TARGET)

CC = g++
CPPFLAGS = -g -Wall -I$(INC_DIR)

$(BIN_TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $@ $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

.PHONY : clean
clean :
	rm -rf $(OBJ_DIR)/*.o