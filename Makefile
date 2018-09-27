ARCH      = ar
ARCHFLAGS = cr
RANLIB    = ranlib

CC 	  = gcc
OPTS	= -O0 -g3 -gdwarf

LIB		=	$(HOME)/.lib/libclib.a
SHARELIB	=	$(HOME)/.lib/libclib.so

SRC_C=$(wildcard *.c)
SRC_CPP=$(wildcard *.cpp)
SRC=$(SRC_C) $(SRC_CPP)

HEAD_C=$(patsubst %.c,%.h, $(SRC_C))
HEAD_CPP=$(patsubst %.cpp,%.h, $(SRC_CPP))
HEAD=$(HEAD_C) $(HEAD_CPP)

OBJ_C=$(patsubst %.c,%.o, $(SRC_C))
OBJ_CPP=$(patsubst %.cpp,%.o, $(SRC_CPP))
OBJ=$(OBJ_C) $(OBJ_CPP)

all: $(LIB) $(SHARELIB)

$(LIB):$(OBJ)
	$(ARCH) $(ARCHFLAGS) $@ $^
	$(RANLIB) $@

$(SHARELIB) : $(OBJ)
	$(CC) -shared -Wall -o $(SHARELIB) $(OBJ) -Wl,--no-undefined,\
	-soname,libclib.so

%.o: %.c,%.h
	$(CC) $(OPTS) -c -o $@ $<

%.o: %.cpp,%.h
	$(CC) $(OPTS) -c -o $@ $<

#		
# --no-undefined, --enable-runtime-pseudo-reloc is used to building and 
# using dll without the dllexport/dllimport attributes.
# windows dll, we should explictly specify that by 
#	#ifdef BUILDING_EXAMPLE_DLL
#	#define EXAMPLE_DLL __declspec(dllexport)
#	#else
#	#define EXAMPLE_DLL __declspec(dllimport)
#	#endif
#
# -Wl, passing following parameters into ld seperated by ',', 
#  NOTE: no space after ','.
#

.PHONYOBJ : cleanobj
cleanobj:
	-rm $(OBJ)

.PHONY : clean
clean:
	-rm  $(LIB) $(SHARELIB) $(OBJ)
