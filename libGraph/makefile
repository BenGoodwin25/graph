#Compiler to use
COMPILER=gcc
#Archiver for static lib
ARCHIVER=ar
#Possible Arguments
CFLAGS=-g -Wall -Wextra -std=c11 -O0
#Here insert the library you could need
LFLAGS=

#Directories for main app
BINDIR=../bin
LIBDIR=../lib
OBJDIR=../obj
SRCDIR=./src
INCDIR=./include
GRAPHSRCDIR=$(SRCDIR)/libgraph
LISTSRCDIR=$(SRCDIR)/liblist

#Defining main exec vars
EXEC=$(BINDIR)/menu
EXECSRC=$(wildcard $(SRCDIR)/*.c)
EXECOBJ=$(EXECSRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

#Defining libgraph vars
LIBGRAPH=$(LIBDIR)/libgraph.a
LIBGRAPHSRC=$(wildcard $(GRAPHSRCDIR)/*.c)
LIBGRAPHOBJ=$(LIBGRAPHSRC:$(GRAPHSRCDIR)/%.c=$(OBJDIR)/%.o)

#Defining liblist vars
LIBLIST=$(LIBDIR)/liblist.a
LIBLISTSRC=$(wildcard $(LISTSRCDIR)/*.c)
LIBLISTOBJ=$(LIBLISTSRC:$(LISTSRCDIR)/%.c=$(OBJDIR)/%.o)

#Compile all targets
all: $(LIBDIR) $(OBJDIR) $(BINDIR) $(EXEC)

#Compile the main exec
$(EXEC): $(EXECOBJ) $(LIBGRAPH) $(LIBLIST)
	$(COMPILER) -static -o $@ $(EXECOBJ) $(CFLAGS) $(LFLAGS) -L$(LIBDIR) -lgraph -llist -I $(INCDIR)

#Creating static graph lib
$(LIBGRAPH) : $(LIBGRAPHOBJ) $(LIBLIST)
	$(ARCHIVER) rcs $@ $(LIBGRAPHOBJ)

#Creating static list lib
$(LIBLIST) : $(LIBLISTOBJ)
	$(ARCHIVER) rcs $@ $^

#Rules for compiling main exec files
$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(COMPILER) -c $< $(CFLAGS) -o $(OBJDIR)/$*.o -I $(INCDIR)

#Rule for compiling lib graph files
$(OBJDIR)/%.o : $(GRAPHSRCDIR)/%.c
	$(COMPILER) -c $< $(CFLAGS) -o $(OBJDIR)/$*.o -I $(INCDIR)

#Rule for compiling lib list files
$(OBJDIR)/%.o : $(LISTSRCDIR)/%.c
	$(COMPILER) -c $< $(CFLAGS) -o $(OBJDIR)/$*.o -I $(INCDIR)

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
