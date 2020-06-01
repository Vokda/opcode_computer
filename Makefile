# This is a template makefile to be used for new projects
# $@ Contains the target file name.
# $< Contains the first dependency file name. 
#
# Declaration of variables
CC = gcc
CC_FLAGS = -Wall -g
OBJECTS_DIR =objects

# File names
EXEC = opcode_computer #name of executable
SOURCES = $(wildcard *.c) #sources
HEADERS = $(wildcard *.h)
obj_files = $(SOURCES:.c=.o)
OBJECTS = $(addprefix $(OBJECTS_DIR)/,$(obj_files))

# Main target
all: $(OBJECTS)
	$(CC) $^ -o $(EXEC) $(LINKS) 

# To obtain object files. Are put in OBJECTS_DIR directory
$(OBJECTS_DIR)/%.o: %.c 
	$(CC) -c $(CC_FLAGS) $< -o $@

# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
