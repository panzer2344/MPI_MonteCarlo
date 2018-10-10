#define _CRT_SECURE_NO_WARNINGS

#include <mpi.h>
#include <iostream>
#include <stdlib.h>
#include <Windows.h>

#include <ctime>
#include <stdio.h>

using namespace std;

/*
time_t rawTime;
struct tm * timeInfo;
char timeBuffer[80];

time(&rawTime);
timeInfo = localtime(&rawTime);

strftime(timeBuffer, 80, "Now it's %I:%M%p.", timeInfo);
cout << timeBuffer << endl;
*/

double function(double x);

int main(int argc, char* argv[]) {
	int size, rank;


	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	MPI_Finalize();

	return 0;
}

double function(double x) {
	return x;
}