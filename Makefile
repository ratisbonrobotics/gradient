DUMMY := $(shell git submodule update --init --recursive)

CC := gcc
CFLAGS := -std=iso9899:1999 -g -Wall -Wextra -Wshadow -Wpedantic -Wstrict-prototypes -Wstrict-aliasing -Wstrict-overflow -Wconversion -Werror -fsanitize=address -fsanitize=undefined -Wl,-z,relro,-z,now -MMD -MP $(shell find . -type d -not -path '*/\.*' | sed 's/^/-I/')
REPO_NAME := $(shell basename `git rev-parse --show-toplevel`)
SRC := $(shell find . -name "*.c")
OBJS := $(SRC:.c=.o)
DEPS := $(OBJS:.o=.d)
TARGET := executable.out

all: $(TARGET)
	@rm -f main.c main.o main.d

$(TARGET): main.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.c:
	echo "extern int main_$(REPO_NAME)(void);" >> main.c
	echo "int main(void) { return main_$(REPO_NAME)(); }" >> main.c

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) main.c main.o null.d