CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Iincludes 
LDFLAGS = -lglfw -lGL -lGLEW -lm

TARGET = snake
SRCS = main.c utils/utils.c math/math.c utils/logger.c
BIN_DIR = bin

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(SRCS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET) $(SRCS) $(LDFLAGS)

run: $(BIN_DIR)/$(TARGET)
	./$(BIN_DIR)/$(TARGET)

clean:
	rm -f $(BIN_DIR)/$(TARGET)
