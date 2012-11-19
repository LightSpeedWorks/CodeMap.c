
all : init bin/test_codemap.out
	echo "*** all ***"

clean : 
	rm obj/*.o bin/*.out
	rmdir obj bin

init :
	mkdir -p obj bin

obj/codemap.o : src/codemap.c src/codemap.h
	cc -o obj/codemap.o -c src/codemap.c 

bin/test_codemap.out : src/test_codemap.c src/codemap.h obj/codemap.o
	cc -o bin/test_codemap.out src/test_codemap.c obj/codemap.o

