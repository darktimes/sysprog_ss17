# Definition der Variablen

# enthaelt die Header Files
HEADERDIR = includes
SHARED_HEADERDIR = ../Shared/includes
SHARED_SRCDIR = ../Shared/src
# enthaelt die Source Files
SRCDIR = src
SYMBOLTABLE_SRCDIR = ../SymbolTable/scr
# enthaelt die Obj Files zum Testen
OBJDIR = objs

# enthaelt das ausfuehrbare File zum Testen
BINDIRTEST = debug

CFLAGS=-g -c -Wall -std=c++11 -I$(HEADERDIR) -I$(SHARED_HEADERDIR) 
#-I$(SYMBOLTABLE_SRCDIR)

# Variante mit guten Makefile-Kenntnissen

makeTestSymbolTable: SymbolTableTarget SymbolStringTarget TestSymbolTableTarget
	g++ -g -std=c++11 $(OBJDIR)/*.o $(BINDIRTEST)/TestSymbolTable.o  -o $(BINDIRTEST)/SymbolTableTest


SymbolTableTarget : $(SRCDIR)/SymbolTable.cpp 
	g++ $(CFLAGS) $(SRCDIR)/SymbolTable.cpp -o $(OBJDIR)/SymbolTable.o

SymbolStringTarget : $(SHARED_SRCDIR)/String.cpp
	g++ $(CFLAGS) $(SHARED_SRCDIR)/String.cpp -o $(OBJDIR)/String.o	
 	
TestSymbolTableTarget : $(SRCDIR)/TestSymbolTable.cpp $(HEADERDIR)/SymbolTable.h
	g++ $(CFLAGS) $(SRCDIR)/TestSymbolTable.cpp -o $(BINDIRTEST)/TestSymbolTable.o  
	




# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren

cleanSymbolTable:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*
#	$(MAKE) makeTestSymbolTable
	
	
	
## objs fuer GesamtProjekt neu erzeugen
SymbolTableOBJTarget:
	$(MAKE) SymbolTableTarget

	
