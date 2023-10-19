SRCDIR:=src
OBJDIR:=obj
INCDIR:=include
LIBDIR:=libs

CC:=clang
CFLAGS=-g -I$(INCDIR) -lm
SRC=$(wildcard $(SRCDIR)/*.c)
OBJ=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC))

all: kalman

kalman: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $@

$(LIBDIR):
	mkdir $(LIBDIR)

$(INCDIR):
	mkdir $(INCDIR)

clean:
	rm -rf $(OBJDIR) kalman

remake: clean
	make
