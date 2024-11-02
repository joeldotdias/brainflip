CFLAGS = -Wall -Wextra -g
SOURCES = main.c parser.c shared.c
TARGET = brainflip

$(TARGET): $(SOURCES)
	@clang $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	@rm -f $(TARGET)
