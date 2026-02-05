all: build lib/libsort.so lib/libsystem_utils.a bin/sort 

CFLAG = -c -W -Wall -Wextra -O0 -g -std=gnu99 
# bibliotheque statique

build/system_utils.o: src/system_utils/system_utils.c
	gcc $(CFLAG) $< -Iinclude -o $@

lib/libsystem_utils.a: build/system_utils.o
	ar -cvq $@ $< 

# bibliotheque dynamique

build/sort.o: src/sort/sort.c
	gcc $(CFLAG) -fPIC $< -Iinclude -o $@

build/demo.o: src/sort/demo.c
	gcc $(CFLAG) -fPIC $< -Iinclude -o $@

lib/libsort.so: build/demo.o build/sort.o
	gcc -shared -o $@ build/demo.o build/sort.o

# edition de lien
bin/sort: apps/Sort.c lib/libsystem_utils.a lib/libsort.so
	gcc -o $@ -Iinclude $< -Llib -lsort -lsystem_utils

# doxygen
doc:
	doxygen Doxyfile

# nettoyage
clean:
	rm -rf build/*
	rm -rf bin/sort

#grand nettoyage
remove:
	rm -rf build/*
	rm -rf bin/*
	rm -rf ./doc

