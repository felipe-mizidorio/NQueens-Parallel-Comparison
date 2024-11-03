N = 15

SRC = ./src/nQueens.c
SRC_OPENMP = ./src/nQueens_openmp.c
SRC_PTHREADS = ./src/nQueens_pthreads.c

EXEC = executable
EXEC_OPENMP = executable_openmp
EXEC_PTHREADS = executable_pthreads

CC = gcc
CFLAGS = -O2 -fopenmp -lpthread

all: $(EXEC) $(EXEC_OPENMP) $(EXEC_PTHREADS)

$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

$(EXEC_OPENMP): $(SRC_OPENMP)
	$(CC) $(CFLAGS) -o $(EXEC_OPENMP) $(SRC_OPENMP)

$(EXEC_PTHREADS): $(SRC_PTHREADS)
	$(CC) $(CFLAGS) -o $(EXEC_PTHREADS) $(SRC_PTHREADS)

run: $(EXEC)
	/usr/bin/time -f "\nTempo real: %e\nTempo de usuário: %U\nTempo de sistema: %S\n" ./$(EXEC) $(N)

run_openmp: $(EXEC_OPENMP)
	/usr/bin/time -f "\nTempo real: %e\nTempo de usuário: %U\nTempo de sistema: %S\n" ./$(EXEC_OPENMP) $(N)

run_pthreads: $(EXEC_PTHREADS)
	/usr/bin/time -f "\nTempo real: %e\nTempo de usuário: %U\nTempo de sistema: %S\n" ./$(EXEC_PTHREADS) $(N)

clean:
	rm -f $(EXEC) $(EXEC_OPENMP) $(EXEC_PTHREADS)

.PHONY: all run run_openmp run_pthreads clean