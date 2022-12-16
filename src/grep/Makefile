CFILES = $(wildcard *.c)
OBJ = $(patsubst %.c, %.o, $(CFILES))
TARGET = s21_grep
CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c11


$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(TARGET) *.o

style:
	clang-format -style=google -i *.c
	clang-format -style=google -i *.h
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h
	
checktest:
	clang-format -style=google -n *.c
	clang-format -style=google -n *.h

rebuild:
	make clean
	make