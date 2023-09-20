CC:=clang
CFLAGS=-g

SRCDIR:=src
OBJDIR:=obj

SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: kalman

kalman: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $<

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) kalman

remake: clean
	make
