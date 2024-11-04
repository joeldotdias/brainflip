COMPILER = clang
CFLAGS = -Wall -Wextra -g
SOURCES = main.c parser.c interpreter.c compiler.c shared.c
TARGET = brainflip

$(TARGET): $(SOURCES)
	@$(COMPILER) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	@rm -f $(TARGET)
