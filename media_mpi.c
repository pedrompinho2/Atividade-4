/*
 * Integrantes:
 *   Pedro Montarroyos de Pinho    - RA 10440213
 *   Felipe Marques Leite Martha   - RA 10437877
 *   Gustavo Kiyoshi Ikeda         - RA 10439179
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc != 2 || atoi(argv[1]) <= 0) {
        if (rank == 0) {
            printf("Uso: mpirun -np <processos> %s <N>\n", argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    int N = atoi(argv[1]);

    float *vetor_local = (float *)malloc(N * sizeof(float));

    srand(time(NULL) + rank);
    for (int i = 0; i < N; i++) {
        vetor_local[i] = rand() / (float)RAND_MAX;
    }

    double soma_local = 0.0;
    for (int i = 0; i < N; i++) {
        soma_local += vetor_local[i];
    }
    double media_local = soma_local / N;

    double soma_global = 0.0;
    MPI_Reduce(&soma_local, &soma_global, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double *somas_locais = NULL;
    double *medias_locais = NULL;
    if (rank == 0) {
        somas_locais = (double *)malloc(size * sizeof(double));
        medias_locais = (double *)malloc(size * sizeof(double));
    }
    MPI_Gather(&soma_local, 1, MPI_DOUBLE, somas_locais, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Gather(&media_local, 1, MPI_DOUBLE, medias_locais, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        for (int i = 0; i < size; i++) {
            printf("[Processo %d] Soma local: %.3f, Média local: %.4f\n",
                   i, somas_locais[i], medias_locais[i]);
        }

        double media_global = soma_global / ((double)N * size);

        printf("\n[Soma global] %.3f\n", soma_global);
        printf("[Média global] %.4f\n", media_global);

        free(somas_locais);
        free(medias_locais);
    }

    free(vetor_local);

    MPI_Finalize();
    return 0;
}
