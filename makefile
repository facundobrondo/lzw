CC = g++
CFLAGS = -Wall -O3

#directorios que tienen headers, -I./include por ejemplo
INCLUDES =
#directorios que tienen bibliotecas, -L./lib
LFLAGS =
#bibliotecas para enlazar, como -lm
LIBS = 
SRCS = main.cpp cmdline.cpp LZW.cpp Dictionary.cpp Symbol.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = tp1
#cantidad máxima de tests a hacer
MAX_TESTS = 25

.PHONY: clean tests make-tests test test-valgrind

all: $(EXEC)
	@echo Se compiló $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(EXEC) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

tests: make-tests test test-valgrind
	@echo all tests ok.

make-tests: tests-gen
	mkdir -p tests
	./tests-gen $(MAX_TESTS)

tests-gen:
	$(CC) $(CFLAGS) $(INCLUDES) -o tests-gen tests.cpp $(LFLAGS) $(LIBS)

test: $(EXEC) make-tests
	@set -e; for t in tests/test-??; do				   \
		echo -e \\n\\n testing: $$t.;				   \
									   \
		echo -e \\nnormal method;				   \
		echo -e \\ncompress;					   \
		time ./$(EXEC) -m normal -p compress -i $$t -o $$t.t;	   \
		echo -e \\ndecompress;					   \
	       	time ./$(EXEC) -m normal -p decompress -i $$t.t -o $$t.tt; \
		diff -b $$t $$t.tt >/dev/null 2>&1;			   \
									   \
		echo -e \\nlist method;					   \
		echo -e \\ncompress;					   \
		time ./$(EXEC) -m list -p compress -i $$t -o $$t.t;	   \
		echo -e \\ndecompress;					   \
		time ./$(EXEC) -m list -p decompress -i $$t.t -o $$t.tt;   \
		diff -b $$t $$t.tt >/dev/null 2>&1;			   \
									   \
		echo -e \\ntree method;					   \
		echo -e \\ncompress;					   \
		time ./$(EXEC) -m tree -p compress -i $$t -o $$t.t;	   \
		echo -e \\ndecompress;					   \
		time ./$(EXEC) -m tree -p decompress -i $$t.t -o $$t.tt;   \
		diff -b $$t $$t.tt >/dev/null 2>&1;			   \
	done
	@echo test ok.

test-valgrind: $(EXEC) make-tests
	@set -e; for t in tests/test-??; do				   \
		echo testing with valgrind: $$t.;			   \
		valgrind --tool=memcheck ./$(EXEC) -p compress		   \
		   -m tree -i $$t -o $$t.t 2>/dev/null;			   \
		valgrind --tool=memcheck ./$(EXEC) -p decompress	   \
	       	   -m tree -i $$t.t -o $$t.tt 2>/dev/null; 		   \
		diff -b $$t $$t.tt >/dev/null 2>&1;			   \
	done
	@echo test ok.

clean:
	rm -vrf *.o *~ $(EXEC) tests-gen tests
