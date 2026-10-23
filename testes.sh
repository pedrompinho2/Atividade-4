#!/usr/bin/env bash

set -e
make -s media_mpi

MPIRUN_OPTS=""
if mpirun --version 2>/dev/null | grep -qi "open mpi"; then
    MPIRUN_OPTS="--oversubscribe"
fi

printf "%-6s %-10s %-18s %-12s\n" "np" "N" "Soma global" "Média global"
for np in 1 2 4 8; do
    for n in 10 1000 100000 1000000; do
        saida=$(mpirun $MPIRUN_OPTS -np "$np" ./media_mpi "$n")
        soma=$(echo "$saida"  | grep "\[Soma global\]"  | awk '{print $3}')
        media=$(echo "$saida" | grep "\[Média global\]" | awk '{print $3}')
        printf "%-6s %-10s %-18s %-12s\n" "$np" "$n" "$soma" "$media"
    done
done
