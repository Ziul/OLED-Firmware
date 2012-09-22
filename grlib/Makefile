include ../Makefile.inc

ROOT_DIR = ..

SRCS = 				\
	canvas.c		\
	circle.c		\
	context.c		\
	imgbutton.c		\
	listbox.c		\
	offscr4bpp.c	\
	pushbutton.c	\
	rectangle.c		\
	string.c		\
	checkbox.c		\
	container.c		\
	image.c			\
	line.c			\
	offscr1bpp.c	\
	offscr8bpp.c	\
	radiobutton.c	\
	slider.c		\
	widget.c
	

#CC_FLAGS = -c -fno-common -O0 -g -std=c99
OBJS = ${SRCS:.c=.o}

.SUFFIXES:.c.o

.c.o:
	@echo -n "Compiling" $< "..."
	$(CC) $(CC_FLAGS) $(INCLUDES) $< -o $(ROOT_DIR)/$(OBJ_DIR)/$@
	@echo "Done."

all: compile

compile: $(OBJS)
