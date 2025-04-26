#include <mpi.h> 
#include <stdio.h> 
 
int main(int argc, char** argv) { 
    MPI_Init(&argc, &argv); 
     
    int world_rank; 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); 
     
    int world_size; 
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); 
     
    if (world_size < 2) { 
        printf("This program requires at least 2 processes\n"); 
        MPI_Finalize(); 
        return 1; 
    } 
     
    if (world_rank == 0) { 
        int number = 12345; 
        MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD); 
        printf("Process 0 sent number %d to process 1\n", number); 
    } else if (world_rank == 1) { 
        int number; 
        MPI_Status status; 
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status); 
        printf("Process 1 received number %d from process 0\n", number); 
    } 
     
    MPI_Finalize(); 
    return 0; 
}
