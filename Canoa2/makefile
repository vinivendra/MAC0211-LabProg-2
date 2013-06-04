execName = ep2
testeName = teste
execOptions =  -g -o $(execName) -lm -lc
testeOptions = -g -o $(testeName) -lm -lc
objOptions = -g -pedantic -Wall -lm -lc
objectsASCII = main.o PrintASCII.o grade.o rio.o util.o pixel.o
objectsTeste = teste.o PrintASCII.o grade.o rio.o util.o pixel.o rotinasTeste.o


.PHONY:ascii
ascii: $(objectsASCII)
	gcc $(objectsASCII) $(execOptions)

.PHONY:teste
teste: $(objectsTeste)
	gcc $(objectsTeste) $(testeOptions)

teste.o: teste.c
	gcc -c teste.c $(objOptions)

main.o: main.c
	gcc -c main.c $(objOptions)

PrintASCII.o: PrintASCII.c
	gcc -c PrintASCII.c $(objOptions)
    
grade.o: grade.c
	gcc -c grade.c $(objOptions)

rio.o: rio.c
	gcc -c rio.c $(objOptions)

util.o: util.c
	gcc -c util.c $(objOptions)

pixel.o: pixel.c
	gcc -c pixel.c $(objOptions)
    
rotinasTeste.o: rotinasTeste.c
	gcc -c rotinasTeste.c $(objOptions)

clean:
	rm -f *.o $(execName)
