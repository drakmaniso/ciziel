CC = gcc
CFLAGS = -Wall -g
LINK = gcc
RM = rm
MKDIR = mkdir


# Source Files

TARGET = compile

#SOURCES = $(SRCDIR)/main.c $(SRCDIR)/global.c $(SRCDIR)/string.c $(SRCDIR)/token.c $(SRCDIR)/scanner.c $(SRCDIR)/parser.c

SRCDIR = src
OBJDIR = build

SOURCES = $(wildcard  $(SRCDIR)/*.c)
OBJECTS = ${subst $(SRCDIR),$(OBJDIR),$(SOURCES:.c=.o)}


#OBJECTS = $(SOURCES:.c=.o)


.PHONY: all clean


all: $(TARGET)


$(TARGET): $(OBJDIR) $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)


$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@


$(OBJDIR):
	$(MKDIR) -p $(OBJDIR)

clean:
	$(RM) $(OBJECTS)
