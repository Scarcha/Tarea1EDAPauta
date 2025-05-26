CC = gcc
SRCS = main.c funciones.c
TARGET = main

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) -o $(TARGET) $(SRCS) -lm
