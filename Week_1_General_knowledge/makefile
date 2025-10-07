LIBNAME = bstrutils
CC = gcc
CFLAGS = -Wall -fPIC

all: main_static main_shared

static: lib$(LIBNAME).a main_static

shared: lib$(LIBNAME).so main_shared

$(LIBNAME).o: $(LIBNAME).c $(LIBNAME).h
	$(CC) $(CFLAGS) -c $(LIBNAME).c -o $(LIBNAME).o

lib$(LIBNAME).a: $(LIBNAME).o
	ar rcs lib$(LIBNAME).a $(LIBNAME).o

lib$(LIBNAME).so: $(LIBNAME).o
	$(CC) -shared -o lib$(LIBNAME).so $(LIBNAME).o

main_static: main.c lib$(LIBNAME).a
	$(CC) main.c -L. -l$(LIBNAME) -o main_static

main_shared: main.c lib$(LIBNAME).so
	$(CC) main.c -L. -l$(LIBNAME) -o main_shared

clean:
	rm -f *.o *.a *.so main_static main_shared