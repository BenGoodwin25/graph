#Compiler to use
COMPILER=gcc
#Archiver for static lib
ARCHIVER=ar
#Possible Arguments
CFLAGS=-g -Wall -Wextra -std=c11 -O0
#Here insert the library you could need
LFLAGS=

#Directories for main app
BINDIR=./bin
LIBDIR=./lib
LIBINCLUDE=./libGraph/include
OBJDIR=./obj
SRCDIR=./src
INCDIR=./include

#Defining main exec vars
EXEC=$(BINDIR)/fatality
EXECSRC=$(wildcard $(SRCDIR)/*.c)
EXECOBJ=$(EXECSRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

#Compile all targets
all: $(LIBDIR) $(OBJDIR) $(BINDIR) compilelib $(EXEC)

#Compile the main exec
$(EXEC): $(EXECOBJ) compilelib
	$(COMPILER) -static -o $@ $(EXECOBJ) $(CFLAGS) $(LFLAGS) -L$(LIBDIR) -lgraph -llist -I $(INCDIR) -I $(LIBINCLUDE)

#Rules for compiling main exec files
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(COMPILER) -c $< $(CFLAGS) -o $(OBJDIR)/$*.o -I $(INCDIR) -I $(LIBINCLUDE)

#Rule libgraph
compilelib :
	cd libGraph && make && cd ../

#Creation of folders
$(OBJDIR) :
	mkdir -p $(OBJDIR)

$(BINDIR) :
	mkdir -p $(BINDIR)

$(LIBDIR) :
	mkdir -p $(LIBDIR)

#Cleaning
clean:
	rm -r $(OBJDIR)

mrproper: clean
	rm -r $(BINDIR)
	rm -r $(LIBDIR)
