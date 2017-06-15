#
#		Targets zum Bauen des Tests
#

# enthaelt die Header Files
HEADERDIR = includes

SHARED_HEADERDIR = ../Shared/includes

SHARED_SRCDIR = ../Shared/src

SCANNER_SRCDIR = ../Scanner/includes
# enthaelt die Source Files
SRCDIR = src

# enthaelt die Obj Files fuer das Gesamtprojekt
OBJDIR = objs

# enthaelt die Objectfiles und das ausfuehrbare File zum Testen des Teilprojekts
BINDIRTEST = debug

CFLAGS=-g -c -Wall -std=c++11 -I$(HEADERDIR) -I$(SHARED_HEADERDIR) -I$(SCANNER_SRCDIR)

#CPPFLAGS=-I$(HEADERDIR) -I$(SHARED_HEADERDIR)
# Linken der Object-files, abhaengig von AutomatTarget und TestAutomatTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestAutomat: AutomatTarget AutomatStatesTarget AutomatStringTarget AutomatTokenTypeTarget TestAutomatTarget
	g++ -g -std=c++11 $(OBJDIR)/*.o $(BINDIRTEST)/*.o -o $(BINDIRTEST)/AutomatTest
	

# compilieren des Files Automat.cpp zu Automat.o, 
# das Objekt-File ist abhängig von src/Automat.cpp und src/Automat.h
# flag:
# -c --> nur compilieren
# -g --> debug Informationen erzeugen
# -Wall --> alle meldungen erzeugen (Warning all)

AutomatTarget :  $(SRCDIR)/Automat.cpp 
	g++ $(CFLAGS) $(SRCDIR)/Automat.cpp -o $(OBJDIR)/Automat.o

AutomatStatesTarget :  $(SRCDIR)/States.cpp
	g++ $(CFLAGS) $(SRCDIR)/States.cpp -o $(OBJDIR)/States.o

AutomatStringTarget: $(SHARED_SRCDIR)/String.cpp
	g++ $(CFLAGS) $(SHARED_SRCDIR)/String.cpp -o $(BINDIRTEST)/String.o	

AutomatTokenTypeTarget: $(SHARED_SRCDIR)/TokenType.cpp
	g++ $(CFLAGS) $(SHARED_SRCDIR)/TokenType.cpp -o $(BINDIRTEST)/TokenType.o	

# TestAutomat.o ist abhängig von src/TestAutomat.cpp und src/Automat.h
TestAutomatTarget :  $(SRCDIR)/TestAutomat.cpp
	g++ $(CFLAGS) $(SRCDIR)/TestAutomat.cpp  -o $(BINDIRTEST)/TestAutomat.o 



# loeschen aller files im verzeichnis obj und debug, dann neu erzeugen

cleanAutomat:
	rm -f objs/*.o
	rm -f debug/*

	
# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer Gesamtprojekt loeschen und dann neu erzeugen
AutomatOBJTarget:
	$(MAKE) AutomatTarget AutomatStatesTarget

