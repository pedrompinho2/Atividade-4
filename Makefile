# Atividade 04 - Pedro (10440213), Felipe (10437877), Gustavo (10439179)
# make            -> compila
# make run        -> roda com 4 processos e N = 1000 (dá pra trocar: make run NP=8 N=5000)
# make testes     -> roda o testes.sh

CC     = mpicc
CFLAGS = -Wall -Wextra -O2
NP    ?= 4
N     ?= 1000
MPIFLAGS ?=

media_mpi: media_mpi.c
	$(CC) $(CFLAGS) -o $@ $<

run: media_mpi
	mpirun $(MPIFLAGS) -np $(NP) ./media_mpi $(N)

testes: media_mpi
	./testes.sh

clean:
	rm -f media_mpi

.PHONY: run testes clean
