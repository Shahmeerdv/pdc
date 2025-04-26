#include <mpi.h> 
#include <stdio.h> 
 
int main(int argc, char** argv) { 
    MPI_Init(&argc, &argv); 
     
    int rank, size; 
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &size); 
     
    if (size < 2) { 
        printf("Need at least 2 processes\n"); 
        MPI_Finalize(); 
        return 1; 
    } 
     
    int data_to_send = rank * 100; 
    int received_data; 
    MPI_Request send_request, recv_request; 
    MPI_Status status; 
     
    if (rank == 0) { 
        MPI_Isend(&data_to_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &send_request); 
        MPI_Irecv(&received_data, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &recv_request); 
        printf("Process 0 is computing while waiting...\n"); 
        for (int i = 0; i < 1000000; i++) {} 
        MPI_Wait(&send_request, MPI_STATUS_IGNORE); 
        MPI_Wait(&recv_request, &status); 
        printf("Process 0 received %d from process 1\n", received_data); 
    }  
    else if (rank == 1) { 
        MPI_Isend(&data_to_send, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &send_request); 
        MPI_Irecv(&received_data, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &recv_request); 
        printf("Process 1 is computing while waiting...\n"); 
        for (int i = 0; i < 1000000; i++) {} 
        MPI_Wait(&send_request, MPI_STATUS_IGNORE); 
        MPI_Wait(&recv_request, &status); 
        printf("Process 1 received %d from process 0\n", received_data); 
    } 
     
    MPI_Finalize(); 
    return 0; 
}
