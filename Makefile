CC:=g++
CFLAGS=-g

SRCDIR:=src
OBJDIR:=obj
INCDIR:=include

SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJ=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: kalman

kalman: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $<

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) kalman

remake: clean
	make
