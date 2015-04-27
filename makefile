# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=g++
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.

CFLAGS=-c -Wall
FLAG=-o $(PNAME).o -g3 -Wall -c
FLAF3= -lSOIL -lopengl32 -lfreeglut -lglu32 -lgdi32 
all:  $(PNAME).o
	$(CC)  $(PNAME).o -o $(PNAME) $(FLAF3)

$(PNAME).o: $(PNAME).cpp
	$(CC) $(FLAG) $(PNAME).cpp

clean:
	del *o $(PNAME).exe
	
	
	