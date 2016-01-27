cio.dll : cio.c cio.h
	gcc -c -g -Wall cio.c
	gcc -shared -Wall -o cio.dll cio.o -Wl,--no-undefined,\
	--enable-runtime-pseudo-reloc,--out-implib,libcio.a

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
	rm *.o

.PHONY : clean
clean:
	rm  *.dll *.a *.o
