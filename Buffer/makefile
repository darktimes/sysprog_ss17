# Definition der Variablen

# enthaelt die Header Files
HEADERDIR = includes

# enthaelt die Source Files
SRCDIR = src

# enthaelt die Obj Files fuer das Gesamtprojekt
OBJDIR = objs

# enthaelt die Objectfiles und das ausfuehrbare File zum Testen des Teilprojekts
BINDIRTEST = debug


CFLAGS=-g -c -Wall -std=c++11 -I$(HEADERDIR) 

#
#		Targets zum Bauen des Tests
#

# Linken der Object-files, abhaengig von BufferTarget und TestBufferTarget
# flag:
# -g --> debug Informationen erzeugen
# -o --> name des output-files

makeTestBuffer: BufferTarget TestBufferTarget FileReaderTarget
	g++ -g -std=c++11 $(OBJDIR)/*.o $(BINDIRTEST)/*.o -o $(BINDIRTEST)/BufferTest
	

# compilieren der Source-files
# Buffer.o ist abhaengig von Buffer.cpp und Buffer.h
# flag:
# -c --> nur compilieren
# -g --> debug Informationen erzeugen
# -Wall --> alle meldungen erzeugen (Warning all)

BufferTarget:  $(SRCDIR)/Buffer.cpp 
	g++ $(CFLAGS) $(SRCDIR)/Buffer.cpp -o $(OBJDIR)/Buffer.o

#TestBuffer.o ist abhaengig von TestBuffer.cpp und Buffer.h
TestBufferTarget:  $(SRCDIR)/TestBuffer.cpp 
	g++ $(CFLAGS) $(SRCDIR)/TestBuffer.cpp -o $(BINDIRTEST)/TestBuffer.o

FileReaderTarget:  $(SRCDIR)/FileReader.cpp 
	g++ $(CFLAGS) $(SRCDIR)/FileReader.cpp -o $(OBJDIR)/FileReader.o

# loeschen aller files im verzeichnis $(OBJDIR) und $(BINDIRTEST) und neu compilieren

cleanBuffer:
	rm -f objs/*.o
	rm -f debug/*

# dieses Target wird vom makefile des Gesamtprojekts verwendet
# objs fuer GesamtProjekt loeschen und dann neu erzeugen
BufferOBJTarget:
	$(MAKE) BufferTarget FileReaderTarget

	
