#include <mpi.h> 
#include <stdio.h> 
#include <stdlib.h> 
 
int main(int argc, char** argv) { 
    MPI_Init(&argc, &argv); 
     
    int rank, size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
     
    const int ROWS = 3, COLS = 4; 
    double matrix[ROWS][COLS]; 
     
    if (rank == 0) { 
        printf("Root initializing matrix:\n"); 
        for (int i = 0; i < ROWS; i++) { 
            for (int j = 0; j < COLS; j++) { 
                matrix[i][j] = i * 10 + j; 
                printf("%.1f ", matrix[i][j]); 
            } 
            printf("\n"); 
        } 
    } 
     
    // Start timing
    double start_time = MPI_Wtime(); 

    MPI_Bcast(matrix, ROWS * COLS, MPI_DOUBLE, 0, MPI_COMM_WORLD); 

    // End timing
    double end_time = MPI_Wtime(); 
    double elapsed_time = end_time - start_time; 

    MPI_Barrier(MPI_COMM_WORLD); 
    for (int p = 0; p < size; p++) { 
        if (rank == p) { 
            printf("Process %d received:\n", rank); 
            for (int i = 0; i < ROWS; i++) { 
                for (int j = 0; j < COLS; j++) { 
                    printf("%.1f ", matrix[i][j]); 
                } 
                printf("\n"); 
            } 
            printf("Elapsed time for MPI_Bcast = %f seconds\n", elapsed_time);
            fflush(stdout); 
        } 
        MPI_Barrier(MPI_COMM_WORLD); 
    }     
     
    MPI_Finalize(); 
    return 0; 
}
