# Definition der Variablen

# enthaelt die Header Files
HEADERDIR = includes
SHARED_HEADERDIR = ../Shared/includes
# enthaelt die Source Files
SRCDIR = src
SYMBOLTABLE_SRCDIR = ../SymbolTable/scr
# enthaelt die Obj Files zum Testen
OBJDIR = objs

# enthaelt das ausfuehrbare File zum Testen
BINDIRTEST = debug

CFLAGS=-g -c -Wall -std=c++11 -I$(HEADERDIR) -I$(SHARED_HEADERDIR) -I$(SYMBOLTABLE_SRCDIR)
## hier alle Object Files eintragen, ausser das File mit der Mainmethode
## darauf achten, dass letzte Zeile ohne "\" eingetragen wird

	#OBJS = $(OBJDIR)/SymbolTable.o \
	#$(OBJDIR)/xx1.o \
	#$(OBJDIR)/xxn.o


#
#		Targets zum Bauen des Tests
#

# Variante mit geringen Makefile-Kenntnissen

## Linken der Object-Files
#makeTestSymbolTable: $(OBJDIR)/SymbolTable.o $(OBJDIR)/TestSymbolTable.o
#	g++ -g $(OBJDIR)/SymbolTable.o $(OBJDIR)/TestSymbolTable.o -o $(BINDIR)/SymbolTableTest
#   cp $(OBJDIR)/SymbolTable.o ../projectOBJs
#
#	
## compilieren der Source-files
#
#$(OBJDIR)/SymbolTable.o :  $(SRCDIR)/SymbolTable.cpp $(HEADERDIR)/SymbolTable.h
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/SymbolTable.o  $(SRCDIR)/SymbolTable.cpp
#
#
#$(OBJDIR)/TestSymbolTable.o :  $(SRCDIR)/TestSymbolTable.cpp $(SRCDIR)/SymbolTable.h
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $(OBJDIR)/TestSymbolTable.o  $(SRCDIR)/TestSymbolTable.cpp
#


# Variante mit guten Makefile-Kenntnissen

makeTestSymbolTable: SymbolTableTarget TestSymbolTableTarget
	g++ -g -std=c++11 $(OBJDIR)/*.o $(BINDIRTEST)/TestSymbolTable.o  -o $(BINDIRTEST)/SymbolTableTest


# $@ name des object files = name auf der linken Seite vom Doppelpunkt des Targets
# $< erste abhaengigkeit, $< das erste Element in der Liste der Abhaengigkeiten
# $@ --> linke Seite vom Doppelpunkt
# $^ --> rechte Seite vom Doppelpunkt


SymbolTableTarget :  $(SRCDIR)/SymbolTable.cpp 
	g++ $(CFLAGS) $(SRCDIR)/SymbolTable.cpp -o $(OBJDIR)/SymbolTable.o

TestSymbolTableTarget: $(SRCDIR)/TestSymbolTable.cpp $(HEADERDIR)/SymbolTable.h
	g++ $(CFLAGS) $(SRCDIR)/TestSymbolTable.cpp -o $(BINDIRTEST)/TestSymbolTable.o  
	


# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren

cleanSymbolTable:
	rm -rf $(OBJDIR)/*.o
	rm -rf $(BINDIRTEST)/*
#	$(MAKE) makeTestSymbolTable
	
	
	
## objs fuer GesamtProjekt neu erzeugen
SymbolTableOBJTarget:
	$(MAKE) SymbolTableTarget

	
