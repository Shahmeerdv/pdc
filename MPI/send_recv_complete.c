#include <mpi.h> 
#include <stdio.h> 
 
int main(int argc, char** argv) { 
    MPI_Init(&argc, &argv); 
     
    int world_rank; 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); 
     
    int world_size; 
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); 
     
    if (world_size < 5) { 
        printf("This program requires at least 5 processes\n"); 
        MPI_Finalize(); 
        return 1; 
    } 
     
    int number = 12345;
    int response;
    MPI_Status status;

    if (world_rank == 0) { 
        double start_time = MPI_Wtime(); // Start timing

        // Send the number to processes 1, 2, 3, and 4
        for (int i = 1; i <= 4; i++) {
            MPI_Send(&number, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Process 0 sent number %d to process %d\n", number, i);
        }

        // Receive responses from processes 1, 2, 3, and 4
        for (int i = 1; i <= 4; i++) {
            MPI_Recv(&response, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            printf("Process 0 received response %d from process %d\n", response, i);
        }

        double end_time = MPI_Wtime(); // End timing
        double elapsed_time = end_time - start_time;
        printf("Elapsed time for communication: %f seconds\n", elapsed_time);

    } else if (world_rank >= 1 && world_rank <= 4) { 
        // Processes 1, 2, 3, and 4 receive number from root
        MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        printf("Process %d received number %d from process 0\n", world_rank, number);

        // Do some "processing" (example: add rank to number)
        response = number + world_rank;

        // Send response back to root
        MPI_Send(&response, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } 
     
    MPI_Finalize(); 
    return 0; 
}
