include ../Makefile.inc

ROOT_DIR = ..

SRCS = 				\
	graphic.c		


OBJS = ${SRCS:.c=.o}

.SUFFIXES:.c.o

.c.o:
	@echo -n "Compiling" $< "..."
	$(CC) $(CC_FLAGS) $(INCLUDES) $< -o $(ROOT_DIR)/$(OBJ_DIR)/$@
	@echo "Done."

all: compile

compile: $(OBJS)
