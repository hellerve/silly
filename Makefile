LIBFILES=silly.c
TESTFILES=$(wildcard tests/*.c)

test:
	gcc $(LIBFILES) $(TESTFILES) -o test_silly
	./test_silly
	rm test_silly
