# Atividade 04 – Cálculo de Média com `MPI_Reduce`

**Integrantes**
- Pedro Montarroyos de Pinho – RA 10440213
- Felipe Marques Leite Martha – RA 10437877
- Gustavo Kiyoshi Ikeda – RA 10439179

## Compilação

```bash
mpicc -o media_mpi media_mpi.c
```

## Execução

```bash
mpirun -np 4 ./media_mpi 1000
```

(Se houver menos núcleos do que processos, use `mpirun --oversubscribe -np 4 ./media_mpi 1000`.)

## Exemplo de saída

```
[Processo 0] Soma local: 498.362, Média local: 0.4984
[Processo 1] Soma local: 485.927, Média local: 0.4859
[Processo 2] Soma local: 509.799, Média local: 0.5098
[Processo 3] Soma local: 501.417, Média local: 0.5014

[Soma global] 1995.506
[Média global] 0.4989
```
