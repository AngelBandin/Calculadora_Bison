CC= gcc -Wall -O0 -ggdb3 -lm
HEADER_FILES_DIR = .
INCLUDES = -I $(HEADER_FILES_DIR)
MAIN= main
SRCS = errores.c tabla_simbolos.c tabla_hash_recolocacion.c lex.yy.c y.tab.c main.c
DEPS = $(HEADER_FILES_DIR)/errores.h tabla_hash_recolocacion.h  tabla_simbolos.h lex.yy.h y.tab.h
OBJS = $(SRCS:.c=.o)
$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) -lm
	rm -f *.o *~
%.o: %.c $(DEPS)
	$(CC) -c $< $(INCLUDES)
cleanall: clean
	rm -f $(MAIN)
clean:
	rm -f *.o *~