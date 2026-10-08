#include <iostream>
#include <omp.h> // Header per le funzioni di libreria OpenMP

int main() {
    int nthreads, tid;

    // Genera un team di thread e fornisce a ciascuno una copia privata delle variabili
#pragma omp parallel private(nthreads, tid)
    {
        // Ottiene il numero (ID) del thread corrente
        tid = omp_get_thread_num();
        printf("Hello World dal thread = %d\n", tid);

        // Solo il master thread (ID 0) esegue questo blocco
        if (tid == 0) {
            nthreads = omp_get_num_threads();
            printf("Numero totale di thread = %d\n", nthreads);
        }
    }
    return 0;
}