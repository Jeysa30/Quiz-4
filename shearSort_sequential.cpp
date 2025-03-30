#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <sys/time.h>

using namespace std;

// Función para tomar el tiempo.
double step(){
	struct timeval tp;
	gettimeofday(&tp, NULL);
	return ((double) tp.tv_sec + (double) tp.tv_usec * 1e-6);
}

// Función de mergesort para ordenar un vector.
void merge(vector<int>& arr, int left, int mid, int right){
	int n1 = mid - left + 1;
	int n2 = right - mid;
	vector<int> L(n1), R(n2);

	for(int i = 0; i < n1; i++){
		L[i] = arr[left + i];
	}

	for(int j = 0; j < n2; j++){
		R[j] = arr[mid + 1 + j];
	}

	int i = 0, j = 0, k = left;

	while(i < n1 && j < n2){
		if(L[i] <= R[j]){
			arr[k] = L[i];
			i++;
		}
		else{
			arr[k] = R[j];
			j++;
		}
		k++;
	}
	while(i < n1){
		arr[k] = L[i];
		i++;
		k++;
	}

	while(j < n1){
		arr[k] = R[j];
		j++;
		k++;
	}
}

void mergeSort(vector<int>& arr, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(arr, left, mid);
		mergeSort(arr, mid + 1, right);
		merge(arr, left, mid, right);
	}
}

// Función para ordenar las filas, par en ascendente e impar en descendente.
void sort_Row(vector<vector<int>>& matrix, int row, bool ascending){
	int n = matrix.size();
	mergeSort(matrix[row], 0, n - 1);
	if(!ascending){
		reverse(matrix[row].begin(), matrix[row].end());
	}
}

// Función para ordenar las columnas de forma descendente.
void sort_Column(vector<vector<int>>& matrix, int col){
	int n = matrix.size();
	vector<int> column(n);
	for (int i = 0; i < n; i++) {
		column[i] = matrix[i][col];
	}

	mergeSort(column, 0, n - 1);
	for (int i = 0; i < n; i++) {
		matrix[i][col] = column[i];
	}
}

// Implementación del shearSort.
void shearSort(vector<vector<int>>& matrix){
	int n = matrix.size();
	int iterations = log2(n) + 1;
	for (int i = 0; i < iterations; i++) {
		for(int row = 0; row < n; row++){
			sort_Row(matrix, row, row % 2 == 0);
		}

		for(int col = 0; col < n; col++){
			sort_Column(matrix, col);
		}
	}
}

// Implememtación del shearSort con transpocisión.
void alternativeShearSort(vector<vector<int>>& matrix){
	int n = matrix.size();
	int repeat = ceil(log2(n)) + 1;
	for(int r = 0; r < repeat; r++){
		for(int i = 0; i < n; i++){
			sort_Row(matrix, i, i % 2 == 0);
		}

		// Transposición.
		vector<vector<int>> transpose(n, vector<int>(n));
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				transpose[j][i] = matrix[i][j];
			}
		}

		// Ordenar filas de la transposición.
		for(int i = 0; i < n; i++){
			sort_Row(transpose, i, true);
		}

		// Volver a transponer.
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				matrix[j][i] = transpose[i][j];
			}
		}
	}
}

// Función para imprimir la matriz.
void printMatrix(const vector<vector<int>>& matrix) {
	for (const auto& row : matrix) {
		for (int val : row) {
			cout << val << " \t";
		}
		cout << endl;
	}
	cout << endl;
}

int main(){
	srand(time(0));
	int n;
	cout << "Ingrese el tamaño de la matriz (n x n): ";
	cin >> n;

	vector<vector<int>> matrix(n, vector<int>(n));

	// Llenar la matriz con valores aleatorios.
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = rand() % 100;
		}
	}

	cout << "\nMatriz original:\n";
	printMatrix(matrix);

	double start = step();
	shearSort(matrix);
	double end = step();
	cout << "Matriz ordenada con ShearSort:\n";
	printMatrix(matrix);
	printf("\nTiempo de ejecución: %f\n", end - start);

	/*
	double start = step();
	alternativeShearSort(matrix);
	double end = step();
	cout << "Matriz ordenada con la transpocisión:\n";
	printMatrix(matrix);
	printf("\nTiempo de ejecución: %f\n", end - start);
	*/

	return 0;
}





