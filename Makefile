CC = gcc
CFLAGS = -Wall -g -std=c99
LINK = gcc
RM = rm
MKDIR = mkdir


# Source Files

TARGET = compile

SRCDIR = src
OBJDIR = build

SOURCES = $(wildcard  $(SRCDIR)/*.c)
HEADERS = $(wildcard  $(SRCDIR)/*.h)
OBJECTS = ${subst $(SRCDIR),$(OBJDIR),$(SOURCES:.c=.o)}


.PHONY: all clean


all: $(TARGET)


$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)


$(OBJDIR)/%.o: src/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJDIR):
	$(MKDIR) -p $(OBJDIR)

clean:
	$(RM) $(OBJECTS)
