# Define the C compiler to use
CC = gcc

# Define the source and include directory
SRC_DIR = code
INC_DIR = code

# Define compiler flags
# -Wall (all warnings), -g (debug symbols), -I$(INC_DIR) (tell compiler where to find headers)
CFLAGS = -Wall -g -I$(INC_DIR)

# Define the name of the final executable file
TARGET = program

# Tell 'make' where to find source files
VPATH = $(SRC_DIR)

# list all object files (.o) that need to be created one for each .c source file
OBJS = main.o platform.o post.o comment.o reply.o

# Define dependencies for each source file
# 'make' will find these headers in the VPATH
PLATFORM_DEPS = platform.h post.h comment.h reply.h
POST_DEPS = post.h comment.h reply.h
COMMENT_DEPS = comment.h reply.h
REPLY_DEPS = reply.h

# The 'all' target is the default one, built when you just type 'make'
all: $(TARGET)

# Rule to link object files and create the final executable
$(TARGET): $(OBJS)
	@echo "Linking..."
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build complete! Run with ./" $(TARGET)

# Rules to compile .c files into .o files
# 'make' will automatically find the .c files and the .h files in VPATH (code/)

main.o: main.c $(PLATFORM_DEPS)
platform.o: platform.c $(PLATFORM_DEPS)
post.o: post.c $(POST_DEPS)
comment.o: comment.c $(COMMENT_DEPS)
reply.o: reply.c $(REPLY_DEPS)

# Rule to clean up build files
clean:
	@echo "Cleaning up..."
	rm -f $(TARGET) $(OBJS)

# Mark 'all' and 'clean' as phony targets
.PHONY: all clean