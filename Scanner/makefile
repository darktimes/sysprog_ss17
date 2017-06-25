# Definition der Variablen

# enthaelt die Header Files
HEADERDIR = includes

# enthaelt die Source Files
SRCDIR = src

# enthaelt die Obj Files zum Testen
OBJDIR = objs

# enthaelt das ausfuehrbare File zum Testen
BINDIRTEST = debug


# enthaelt die Header Files
HEADERDIR = includes

# enthaelt die Source Files
SRCDIR = src

SYMTABLE_DIR = ../SymbolTable
BUFFER_DIR = ../Buffer
SHARED_DIR = ../Shared
AUTOMAT_DIR = ../Automat
PARSER_DIR = ../Parser

#SHARED_SRCDIR = ../Shared/src

# enthaelt die Obj Files fuer das Gesamtprojekt
OBJDIR = objs

# enthaelt die Objectfiles und das ausfuehrbare File zum Testen des Teilprojekts

CFLAGS=-g -c -Wall -std=c++11 -I$(HEADERDIR) -I$(SHARED_DIR)/$(HEADERDIR) -I$(AUTOMAT_DIR)/$(HEADERDIR) -I$(SYMTABLE_DIR)/$(HEADERDIR) -I$(BUFFER_DIR)/$(HEADERDIR) -I$(PARSER_DIR)/$(HEADERDIR)

CPPFLAGS=-I$(HEADERDIR) 

makeTestScanner: ScannerTarget TokensTarget TestScannerTarget
	g++ -g -std=c++11 $(OBJDIR)/*.o $(BINDIRTEST)/*.o $(SHARED_DIR)/$(OBJDIR)/*.o $(AUTOMAT_DIR)/$(OBJDIR)/*.o $(BUFFER_DIR)/$(OBJDIR)/*.o $(SYMTABLE_DIR)/$(OBJDIR)/*.o -o $(BINDIRTEST)/Scanner

ScannerTarget :  $(SRCDIR)/Scanner.cpp 
	g++ $(CFLAGS) $(SRCDIR)/Scanner.cpp -o $(OBJDIR)/Scanner.o


TokensTarget : $(SRCDIR)/Tokens.cpp
	g++ $(CFLAGS) $(SRCDIR)/Tokens.cpp -o $(OBJDIR)/Tokens.o

TestScannerTarget :  $(SRCDIR)/TestScanner.cpp
	g++ $(CFLAGS) $(SRCDIR)/TestScanner.cpp  -o $(BINDIRTEST)/TestScanner.o


cleanScanner:
	rm -f objs/*.o
	rm -f debug/*
	
# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer Gesamtprojekt loeschen und dann neu erzeugen
ScannerOBJTarget:
	$(MAKE) makeTestScanner


#SYMBOLTABLEDIR = ../Symboltable
#
#SHAREDDIR = ../Shared
#
#
### hier alle Object Files eintragen, ausser das File mit der Mainmethode
### darauf achten, dass letzte Zeile ohne "\" eingetragen wird
#
#OBJS = $(OBJDIR)/Scanner.o \
#	#$(OBJDIR)/xx1.o \
#	#$(OBJDIR)/xxn.o
#
#
### Variante mit wenig Makefile-Kenntnissen
## 
### linken der Object-files 
##makeTestScanner: $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o
##	g++ -g $(OBJDIR)/Scanner.o $(OBJDIR)/TestScanner.o   $(PROJECTOBJDIR)/Automat/*.o $(PROJECTOBJDIR)/Buffer/*.o $(PROJECTOBJDIR)/Symboltable/*.o -o $(BINDIRTEST)/ScannerTest
###	
###	
###	
#### compilieren der source-files
##$(OBJDIR)/Scanner.o :  $(SRCDIR)/Scanner.cpp $(HEADERDIR)/Scanner.h
##	@echo "g++ $*.cpp"
##	g++ -g  -c -Wall  -o $(OBJDIR)/Scanner.o  $(SRCDIR)/Scanner.cpp
##	cp $(OBJDIR)/Scanner.o $(PROJECTOBJDIR)/Scanner
###
##$(OBJDIR)/TestScanner.o :  $(SRCDIR)/TestScanner.cpp 
##	@echo "g++ $*.cpp"
##	g++ -g  -c -Wall  -o $(OBJDIR)/TestScanner.o  $(SRCDIR)/TestScanner.cpp
##
#	
#	
## Variante mit guten Makefile-Kenntnissen
#makeTestScanner: $(OBJS) ScannerTest
#
#
#$(OBJDIR)/%.o :  $(SRCDIR)/%.cpp $(HEADERDIR)/%.h
#	@echo "g++ $*.cpp"
#	g++ -g  -c -Wall  -o $@  $<
#
## 
## $@ name des object files
## $< erste abhaengigkeit
#
#
#ScannerTest: $(SRCDIR)/TestScanner.cpp $(HEADERDIR)/Scanner.h
#	g++ -g  -c -Wall src/TestScanner.cpp -o $(BINDIRTEST)/TestScanner.o  
#	g++ -g $(BINDIRTEST)/TestScanner.o $(OBJDIR)/*.o $(AUTOMATDIR)/$(OBJDIR)/*.o $(BUFFERDIR)/$(OBJDIR)/*.o $(SHAREDDIR)/$(OBJDIR)/*.o $(SYMBOLTABLEDIR)/$(OBJDIR)/*.o -o $(BINDIRTEST)/ScannerTest
#
## loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu erstellen
#
#cleanScanner:
#	rm -rf $(OBJDIR)/*.o
#	rm -rf $(BINDIRTEST)/*
##	$(MAKE) makeTestScanner
#
#
