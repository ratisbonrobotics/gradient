DUMMY := $(shell git submodule update --init --recursive)

# Common settings
CC := gcc
REPO_NAME := $(shell basename `git rev-parse --show-toplevel`)
SRC := $(shell find . -name "*.c")
OBJS := $(SRC:.c=.o)
DEPS := $(OBJS:.o=.d)
TARGET := executable.out

# Base flags
CFLAGS_BASE := -std=iso9899:1999 -Wall -Wextra -Wshadow -Wpedantic -Wstrict-prototypes -Wstrict-aliasing -Wstrict-overflow -Wconversion -Werror -Wl,-z,relro,-z,now -MMD -MP $(shell find . -type d -not -path '*/\.*' | sed 's/^/-I/')

# Debug settings
CFLAGS_DEBUG := $(CFLAGS_BASE) -g -fsanitize=address -fsanitize=undefined

# Release with assert settings
CFLAGS_RELEASE_ASSERT := $(CFLAGS_BASE) -O3 -march=native -funroll-loops -flto

# Release settings (no assert)
CFLAGS_RELEASE := $(CFLAGS_RELEASE_ASSERT) -DNDEBUG

# Default target
all: debug

# Debug target
debug: CFLAGS := $(CFLAGS_DEBUG)
debug: $(TARGET)
	@rm -f main.c main.o main.d

# Release with assert target
release_assert: CFLAGS := $(CFLAGS_RELEASE_ASSERT)
release_assert: $(TARGET)
	@rm -f main.c main.o main.d

# Release target (no assert)
release: CFLAGS := $(CFLAGS_RELEASE)
release: $(TARGET)
	@rm -f main.c main.o main.d

# Target rules
$(TARGET): main.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.c:
	echo "extern int main_$(REPO_NAME)(void);" > main.c
	echo "int main(void) { return main_$(REPO_NAME)(); }" >> main.c

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS) $(TARGET) main.c main.o null.d
