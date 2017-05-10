# enthaelt die Header Files
HEADERDIR = includes

# enthaelt die Source Files
SRCDIR = src

# enthaelt die Obj Files fuer das Gesamtprojekt
OBJDIR = objs

# enthaelt die Objectfiles und das ausfuehrbare File zum Testen des Teilprojekts

CFLAGS=-g -c -Wall -std=c++11

CPPFLAGS=-I$(HEADERDIR) 

String: $(SRCDIR)/String.cpp
	g++ $(CFLAGS) $(SRCDIR)/String.cpp -o $(OBJDIR)/String.o	


cleanShared:
	rm -f objs/*.o
	rm -f debug/*
	
# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer Gesamtprojekt loeschen und dann neu erzeugen
SharedOBJTarget:
	$(MAKE) String

