#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

/*int main(int argc, char** argv)
{
	const int VECTOR_SIZE = 8;

	int vector[VECTOR_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int rank, size;
	int *recvVector;
	int result = 0;

	MPI_Status status;

	MPI_Init(&argc, &argv);
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	int oblongSize, normalSize, countAdditionalWorkProc, countNormalWorkProc;
	
	countAdditionalWorkProc = VECTOR_SIZE % size;
	oblongSize = normalSize = VECTOR_SIZE / size;
	if (countAdditionalWorkProc > 0) {
		oblongSize = normalSize + 1;
	}

	if (rank == 0) {
		int i = (countAdditionalWorkProc > 0) ? 1 : 0;
		for (; i < countAdditionalWorkProc; i++) {
			cout << "Send data to process #" << i << endl;
			MPI_Send(&vector[i * oblongSize], oblongSize, MPI_INT, i, 0, MPI_COMM_WORLD);
			cout << "Data sended" << endl;

			Sleep(1000);
		}
		
		int j = (countAdditionalWorkProc > 0) ? i : 1;
		for (; j < size; j++) {
			cout << "Send data to process #" << j << endl;
			MPI_Send(&vector[i * oblongSize + (j - i) * normalSize], normalSize, MPI_INT, j, 0, MPI_COMM_WORLD);
			cout << "Data sended" << endl;

			Sleep(1000);
		}

		recvVector = new int[oblongSize];
		for (int i = 0; i < oblongSize; i++) {
			result += vector[i];
		}
		delete[] recvVector;

		recvVector = new int[size];

		for (int j = 1; j < size; j++) {
			cout << "Recieved data from process #" << j << endl;
			MPI_Recv(recvVector + j, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			cout << "Recieved from " << status.MPI_SOURCE << " : " << *(recvVector + j) << endl;
			result += *(recvVector + j);

			Sleep(1000);
		}

		cout << "Result = " << result << endl;
	}
	else {
		if (rank < countAdditionalWorkProc) {
			recvVector = new int[oblongSize];

			cout << "Recieved data in process #" << rank << endl;
			MPI_Recv(&recvVector, oblongSize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			cout << "Data recieved in process #" << rank << endl;

			cout << "First element of vector:" << recvVector[0] << endl;
			cout << "Error is: " << status.MPI_ERROR << endl;
			

			Sleep(1000);

			for (int i = 0; i < oblongSize; i++) {
				result += recvVector[i];
			}
			cout << "Result in process #" << rank << " = " << result << endl;
		}
		else {
			recvVector = new int[normalSize];
			
			cout << "Recieved data in process #" << rank << endl;
			MPI_Recv(&recvVector, normalSize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
			cout << "Data recieved in process #" << rank << endl;

			cout << "First element of vector:" << recvVector[0] << endl;
			cout << "Error is: " << status.MPI_ERROR << endl;

			Sleep(1000);

			for (int i = 0; i < normalSize; i++) {
				result += recvVector[i];
			}
			cout << "Result in process #" << rank << " = " << result << endl;
		}

		cout << "Send data to host" << endl;
		MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		cout << "Data sended" << endl;

		Sleep(1000);
	}

	delete[] recvVector;
	MPI_Finalize();
	
	Sleep(2000);
	return 0;
}*/


int main(int argc, char* argv[]) {
	const int VECTOR_SIZE = 8;

	int vector[VECTOR_SIZE] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	int *resultVector;
	int size, rank;
	int result = 0;

	MPI_Status status;

	int partVectorSize;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	partVectorSize = VECTOR_SIZE / size;

	if (rank == 0) {
		for (int i = 1; i < size; i++) {
			MPI_Send(&vector[i * partVectorSize], partVectorSize, MPI_INT, i, 0, MPI_COMM_WORLD);
		}

		for (int i = 1; i < size; i++) {
			int tmp;
			MPI_Recv(&tmp, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
			result += tmp;
		}

		for (int i = 0; i < partVectorSize; i++) {
			result += vector[i];
		}
	}
	else {
		resultVector = new int[partVectorSize];

		MPI_Recv(resultVector, partVectorSize, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
		for (int i = 0; i < partVectorSize; i++) {
			result += resultVector[i];
		}

		MPI_Send(&result, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	delete[] resultVector;
	MPI_Finalize();

	cout << "result = " << result << endl;
	Sleep(2000);

	return 0;
}