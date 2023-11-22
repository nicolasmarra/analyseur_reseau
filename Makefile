CC ?= gcc
CFLAGS ?= -Wall -Wextra -Werror -g
LDLIBS ?= -lm 
LDFLAGS ?= -lpcap


INCLUDEDIR = include
SRCDIR   = src
OBJDIR = obj
BINDIR = bin

TARGET = $(BINDIR)/analyseur


SRC := $(wildcard $(SRCDIR)/*.c)
INCLUDES := $(wildcard $(INCLUDEDIR)/*.h)
OBJ := $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)


$(TARGET): $(OBJ)
	mkdir -p $(BINDIR)	
	$(CC) -o $@ $^ $(CFLAGS) $(LDLIBS) $(LDFLAGS)
	@echo "Linking complete!"

$(OBJ): $(OBJDIR)/%.o:  $(SRCDIR)/%.c $(INCLUDES)
	mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(CFLAGS) -I$(INCLUDEDIR)

.PHONY: clean cov
clean:
	rm -rf $(OBJDIR)/* $(TARGET)

